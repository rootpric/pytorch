// Copyright 2004-present Facebook. All Rights Reserved.

#include <ATen/native/UpSample.h>
#include <c10/util/irange.h>

namespace at {
namespace native {
namespace upsample {

TORCH_API c10::SmallVector<int64_t, 3> compute_output_size(
    c10::IntArrayRef input_size,  // Full input tensor size.
    at::OptionalIntArrayRef output_size,
    c10::optional<c10::ArrayRef<double>> scale_factors) {
  const auto spatial_dimensions = static_cast<int64_t>(input_size.size()) - 2;
  if (output_size) {
    TORCH_CHECK(!scale_factors, "Must specify exactly one of output_size and scale_factors");
    TORCH_CHECK(static_cast<int64_t>(output_size->size()) == spatial_dimensions);
    return {output_size->data(), output_size->data() + output_size->size()};
  }
  if (scale_factors) {
    TORCH_CHECK(!output_size, "Must specify exactly one of output_size and scale_factors");
    TORCH_CHECK(static_cast<int64_t>(scale_factors->size()) == spatial_dimensions);
    c10::SmallVector<int64_t, 3> ret;
    for (const auto i : c10::irange(spatial_dimensions)) {
      ret.push_back(static_cast<double>(input_size[i+2]) * scale_factors.value()[i]);
    }
    return ret;
  }
  TORCH_CHECK(false, "Must specify exactly one of output_size and scale_factors");
}

} // namespace upsample
} // namespace native
} // namespace at
