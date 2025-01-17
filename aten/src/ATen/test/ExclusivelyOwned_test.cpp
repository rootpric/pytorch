#include <gtest/gtest.h>

#include <ATen/NativeFunctions.h>
#include <ATen/Tensor.h>
#include <c10/util/ExclusivelyOwned.h>
#include <c10/util/intrusive_ptr.h>

#include <string>

namespace {

using at::Tensor;

template <typename T>
class ExclusivelyOwnedTest : public ::testing::Test {
 public:
  c10::ExclusivelyOwned<T> defaultConstructed;
  c10::ExclusivelyOwned<T> sample;
 protected:
  void SetUp() override; // defined below helpers
  void TearDown() override {
    defaultConstructed = c10::ExclusivelyOwned<T>();
    sample = c10::ExclusivelyOwned<T>();
  }
};

template <typename T>
T getSampleValue();

template <>
Tensor getSampleValue() {
  return at::native::zeros({2, 2}).to(at::kCPU);
}

template <typename T>
void assertIsSampleObject(const T& eo);

template <>
void assertIsSampleObject<Tensor>(const Tensor& t) {
  EXPECT_EQ(t.sizes(), (c10::IntArrayRef{2, 2}));
  EXPECT_EQ(t.strides(), (c10::IntArrayRef{2, 1}));
  ASSERT_EQ(t.scalar_type(), at::ScalarType::Float);
  static const float zeros[4] = {0};
  EXPECT_EQ(memcmp(zeros, t.data_ptr(), 4 * sizeof(float)), 0);
}


template <typename T>
void ExclusivelyOwnedTest<T>::SetUp() {
  defaultConstructed = c10::ExclusivelyOwned<T>();
  sample = c10::ExclusivelyOwned<T>(getSampleValue<T>());
}

using ExclusivelyOwnedTypes = ::testing::Types<
  Tensor
  >;

TYPED_TEST_CASE(ExclusivelyOwnedTest, ExclusivelyOwnedTypes);

TYPED_TEST(ExclusivelyOwnedTest, DefaultConstructor) {
  c10::ExclusivelyOwned<TypeParam> defaultConstructed;
}

TYPED_TEST(ExclusivelyOwnedTest, MoveConstructor) {
  auto movedDefault = std::move(this->defaultConstructed);
  auto movedSample = std::move(this->sample);

  assertIsSampleObject(*movedSample);
}

TYPED_TEST(ExclusivelyOwnedTest, MoveAssignment) {
  // Move assignment from a default-constructed ExclusivelyOwned is handled in
  // TearDown at the end of every test!
  c10::ExclusivelyOwned<TypeParam> anotherSample = c10::ExclusivelyOwned<TypeParam>(getSampleValue<TypeParam>());
  anotherSample = std::move(this->sample);
  assertIsSampleObject(*anotherSample);
}

TYPED_TEST(ExclusivelyOwnedTest, MoveAssignmentFromContainedType) {
  c10::ExclusivelyOwned<TypeParam> anotherSample = c10::ExclusivelyOwned<TypeParam>(getSampleValue<TypeParam>());
  anotherSample = getSampleValue<TypeParam>();
  assertIsSampleObject(*anotherSample);
}

TYPED_TEST(ExclusivelyOwnedTest, Take) {
  auto x = std::move(this->sample).take();
  assertIsSampleObject(x);
}

} // namespace

extern "C" void inspectTensor() {
  auto t = getSampleValue<at::Tensor>();
}

extern "C" void inspectExclusivelyOwnedTensor() {
  c10::ExclusivelyOwned<Tensor> t(getSampleValue<at::Tensor>());
}
