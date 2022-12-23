#ifndef CAFFE2_OPERATORS_ELU_OP_H_
#define CAFFE2_OPERATORS_ELU_OP_H_

#include <vector>

#include "caffe2/operators/elementwise_ops.h"

namespace caffe2 {

template <class Context>
struct EluFunctor {
  explicit EluFunctor(OperatorBase& op)
      : alpha(op.GetSingleArgument<float>("alpha", 1.0f)) {}

  template <typename T>
  bool operator()(const int N, const T* X, T* Y, Context* context) const;

  const float alpha;
};

template <class Context>
struct EluGradientFunctor {
  explicit EluGradientFunctor(OperatorBase& op)
      : alpha(op.GetSingleArgument<float>("alpha", 1.0f)) {}

  template <typename T>
  bool Forward(
      const std::vector<int>& Y_dims,
      const std::vector<int>& dY_dims,
      const T* Y,
      const T* dY,
      T* dX,
      Context* context) const;

  const float alpha;
};

} // namespace caffe2

#endif // CAFFE2_OPERATORS_ELU_OP_H_
