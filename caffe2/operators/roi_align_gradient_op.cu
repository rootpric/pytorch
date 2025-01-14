#include "caffe2/operators/roi_align_gradient_op.h"

#include <stdio.h>
#include <cfloat>
#include "caffe2/core/context_gpu.h"
#include "caffe2/utils/GpuAtomics.cuh"
#include "caffe2/utils/math.h"

namespace caffe2 {

namespace {

template <typename T>
__device__ void bilinear_interpolate_gradient(
    const int height,
    const int width,
    T y,
    T x,
    T& w1,
    T& w2,
    T& w3,
    T& w4,
    int& x_low,
    int& x_high,
    int& y_low,
    int& y_high) {
  // deal with cases that inverse elements are out of feature map boundary
  if (y < -1.0 || y > height || x < -1.0 || x > width) {
    // empty
    w1 = w2 = w3 = w4 = 0.;
    x_low = x_high = y_low = y_high = -1;
    return;
  }

  if (y <= 0) {
    y = 0;
  }
  if (x <= 0) {
    x = 0;
  }

  y_low = (int)y;
  x_low = (int)x;

  if (y_low >= height - 1) {
    y_high = y_low = height - 1;
    y = (T)y_low;
  } else {
    y_high = y_low + 1;
  }

  if (x_low >= width - 1) {
    x_high = x_low = width - 1;
    x = (T)x_low;
  } else {
    x_high = x_low + 1;
  }

  T ly = y - y_low;
  T lx = x - x_low;
  T hy = 1. - ly, hx = 1. - lx;

  // reference in forward
  // T v1 = bottom_data[y_low * width + x_low];
  // T v2 = bottom_data[y_low * width + x_high];
  // T v3 = bottom_data[y_high * width + x_low];
  // T v4 = bottom_data[y_high * width + x_high];
  // T val = (w1 * v1 + w2 * v2 + w3 * v3 + w4 * v4);

  w1 = hy * hx, w2 = hy * lx, w3 = ly * hx, w4 = ly * lx;

  return;
}

template <typename T>
__global__ void RoIAlignBackwardFeature(
    const int nthreads,
    const T *const top_diff,
    const T spatial_scale,
    const int channels,
    const int height,
    const int width,
    const int pooled_height,
    const int pooled_width,
    const int sampling_ratio,
    T *const bottom_diff,
    const T *const bottom_rois,
    bool continuous_coordinate) {
  CUDA_1D_KERNEL_LOOP(index, nthreads) {
    // (n, c, ph, pw) is an element in the pooled output
    const int pw = index % pooled_width;
    const int ph = (index / pooled_width) % pooled_height;
    const int c = (index / pooled_width / pooled_height) % channels;
    const int n = index / pooled_width / pooled_height / channels;

    const T *const offset_bottom_rois = bottom_rois + n * 5;
    const int roi_batch_ind = offset_bottom_rois[0];

    // Do not using rounding; this implementation detail is critical
    T roi_offset = continuous_coordinate ? T(0.5) : 0;
    T roi_start_w = offset_bottom_rois[1] * spatial_scale - roi_offset;
    T roi_start_h = offset_bottom_rois[2] * spatial_scale - roi_offset;
    T roi_end_w = offset_bottom_rois[3] * spatial_scale - roi_offset;
    T roi_end_h = offset_bottom_rois[4] * spatial_scale - roi_offset;

    T roi_width = roi_end_w - roi_start_w;
    T roi_height = roi_end_h - roi_start_h;
    if (!continuous_coordinate) { // backward compatibility
      // Force malformed ROIs to be 1x1
      roi_width = c10::cuda::compat::max(roi_width, (T)1.);
      roi_height = c10::cuda::compat::max(roi_height, (T)1.);
    }
    T bin_size_h = static_cast<T>(roi_height) / static_cast<T>(pooled_height);
    T bin_size_w = static_cast<T>(roi_width) / static_cast<T>(pooled_width);

    T* offset_bottom_diff =
        bottom_diff + (roi_batch_ind * channels + c) * height * width;

    int top_offset = (n * channels + c) * pooled_height * pooled_width;
    const T* offset_top_diff = top_diff + top_offset;
    const T top_diff_this_bin = offset_top_diff[ph * pooled_width + pw];

    // We use roi_bin_grid to sample the grid and mimic integral
    int roi_bin_grid_h = (sampling_ratio > 0)
        ? sampling_ratio
        : ceil(roi_height / pooled_height); // e.g., = 2
    int roi_bin_grid_w =
        (sampling_ratio > 0) ? sampling_ratio : ceil(roi_width / pooled_width);

    // We do average (integral) pooling inside a bin
    const T count = roi_bin_grid_h * roi_bin_grid_w; // e.g. = 4

    for (int iy = 0; iy < roi_bin_grid_h; iy++) // e.g., iy = 0, 1
    {
      const T y = roi_start_h + ph * bin_size_h +
          static_cast<T>(iy + .5f) * bin_size_h /
              static_cast<T>(roi_bin_grid_h); // e.g., 0.5, 1.5
      for (int ix = 0; ix < roi_bin_grid_w; ix++) {
        const T x = roi_start_w + pw * bin_size_w +
            static_cast<T>(ix + .5f) * bin_size_w /
                static_cast<T>(roi_bin_grid_w);

        T w1, w2, w3, w4;
        int x_low, x_high, y_low, y_high;

        bilinear_interpolate_gradient(
            height,
            width,
            y,
            x,
            w1,
            w2,
            w3,
            w4,
            x_low,
            x_high,
            y_low,
            y_high);

        T g1 = top_diff_this_bin * w1 / count;
        T g2 = top_diff_this_bin * w2 / count;
        T g3 = top_diff_this_bin * w3 / count;
        T g4 = top_diff_this_bin * w4 / count;

        if (x_low >= 0 && x_high >= 0 && y_low >= 0 && y_high >= 0) {
          gpu_atomic_add(
              offset_bottom_diff + y_low * width + x_low, static_cast<T>(g1));
          gpu_atomic_add(
              offset_bottom_diff + y_low * width + x_high, static_cast<T>(g2));
          gpu_atomic_add(
              offset_bottom_diff + y_high * width + x_low, static_cast<T>(g3));
          gpu_atomic_add(
              offset_bottom_diff + y_high * width + x_high, static_cast<T>(g4));
        } // if
      } // ix
    } // iy
  } // CUDA_1D_KERNEL_LOOP
} // RoIAlignBackward

} // namespace

template <>
C10_EXPORT bool RoIAlignGradientOp<float, CUDAContext>::RunOnDevice() {
  auto& X = Input(0); // Input data to pool
  auto& R = Input(1); // RoIs
  auto& dY = Input(2); // Gradient of net w.r.t. output of "forward" op
                       // (aka "gradOutput")

  auto* dX = Output(
      0, X.sizes(), at::dtype<float>()); // Gradient of net w.r.t. input to
                                         // "forward" op (aka "gradInput")

  // Must zero-out dX before accumulating gradients
  // (TODO): Kaiming - is this safe?
  math::Set<float, CUDAContext>(
      dX->numel(), 0.f, dX->template mutable_data<float>(), &context_);

  if (dY.numel() > 0) { // Handle possibly empty gradient if there were no rois
    RoIAlignBackwardFeature<float>
        <<<CAFFE_GET_BLOCKS(dY.numel()),
           CAFFE_CUDA_NUM_THREADS,
           0,
           context_.cuda_stream()>>>(
            dY.numel(),
            dY.data<float>(),
            spatial_scale_,
            X.dim32(1),
            X.dim32(2),
            X.dim32(3),
            pooled_height_,
            pooled_width_,
            sampling_ratio_,
            dX->template mutable_data<float>(),
            R.data<float>(),
            aligned_);
    C10_CUDA_KERNEL_LAUNCH_CHECK();
  }
  return true;
}

REGISTER_CUDA_OPERATOR(
    RoIAlignGradient,
    RoIAlignGradientOp<float, CUDAContext>);

template <typename T>
using RoIAlignGradientCUDAOp = RoIAlignGradientOp<T, CUDAContext>;

} // namespace caffe2

C10_EXPORT_CAFFE2_OP_TO_C10_CUDA(
    RoIAlignGradient,
    caffe2::RoIAlignGradientCUDAOp<float>);
