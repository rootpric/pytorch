#define TORCH_ASSERT_NO_OPERATORS
#include <ATen/Dispatch.h>
#include <ATen/native/DispatchStub.h>
#include <ATen/native/cuda/Loops.cuh>
#include <ATen/native/cuda/JitLoops.cuh>
#include <ATen/native/TensorIterator.h>
#include <ATen/native/BinaryOps.h>

// NOTE: CUDA on Windows requires that the enclosing function
// of a __device__ lambda not have internal linkage.

namespace at { namespace native {

const char logical_and_name[] = "logical_and_kernel";
void logical_and_kernel_cuda(TensorIterator& iter) {
  auto dtype = iter.common_dtype();
  if (at::isComplexType(dtype)) {
#if AT_USE_JITERATOR()
    static const auto logical_and_string = jiterator_stringify(
        template <typename T>
        T logical_and_kernel(T a, T b) {
          return a && b;
        }
    ); // logical_and_string
    AT_DISPATCH_COMPLEX_TYPES(dtype, "logical_and_cuda", [&]() {
      jitted_gpu_kernel<
        /*name=*/ logical_and_name,
        /*return_dtype=*/ scalar_t,
        /*common_dtype=*/ scalar_t,
        /*arity=*/ 2>(iter, logical_and_string);
    }); // logical_and_string
#else
    AT_DISPATCH_COMPLEX_TYPES(dtype, "logical_and_cuda", [&]() {
      gpu_kernel_with_scalars(iter, []GPU_LAMBDA(scalar_t a, scalar_t b) -> bool {
        return a && b;
      });
    });
#endif
  } else {
    AT_DISPATCH_ALL_TYPES_AND3(kHalf, kBool, ScalarType::BFloat16,
                               dtype, "logical_and_cuda", [&]() {
      gpu_kernel_with_scalars(iter, []GPU_LAMBDA(scalar_t a, scalar_t b) -> bool {
        return a && b;
      });
   });
  }
}

void logical_or_kernel_cuda(TensorIterator& iter) {
  AT_DISPATCH_ALL_TYPES_AND_COMPLEX_AND3(kHalf, kBool, ScalarType::BFloat16,
                                         iter.common_dtype(), "logical_or_cuda", [&]() {
    gpu_kernel_with_scalars(iter, []GPU_LAMBDA(scalar_t a, scalar_t b) -> bool {
      return a || b;
    });
  });
}

void logical_xor_kernel_cuda(TensorIterator& iter) {
  AT_DISPATCH_ALL_TYPES_AND_COMPLEX_AND3(kHalf, kBool, ScalarType::BFloat16,
                                         iter.common_dtype(), "logical_xor_cuda", [&]() {
    gpu_kernel_with_scalars(iter, []GPU_LAMBDA(scalar_t a, scalar_t b) -> bool {
      return bool(a) != bool(b);
    });
  });
}

REGISTER_DISPATCH(logical_and_stub, &logical_and_kernel_cuda);
REGISTER_DISPATCH(logical_or_stub, &logical_or_kernel_cuda);
REGISTER_DISPATCH(logical_xor_stub, &logical_xor_kernel_cuda);


}} // namespace at::native
