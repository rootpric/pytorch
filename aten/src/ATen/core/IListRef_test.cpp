#include <ATen/Functions.h>
#include <ATen/core/IListRef.h>
#include <ATen/core/Tensor.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <iterator>

using namespace c10;

static std::vector<at::Tensor> get_tensor_vector() {
  std::vector<at::Tensor> tensors;
  const size_t SIZE = 5;
  for (size_t i = 0; i < SIZE; i++) {
    tensors.emplace_back(at::empty({0}));
  }
  return tensors;
}

static std::vector<optional<at::Tensor>> get_boxed_opt_tensor_vector() {
  std::vector<optional<at::Tensor>> optional_tensors;
  const size_t SIZE = 5;
  for (size_t i = 0; i < SIZE * 2; i++) {
    auto opt_tensor = (i % 2 == 0) ? optional<at::Tensor>(at::empty({0})) : nullopt;
    optional_tensors.emplace_back(opt_tensor);
  }
  return optional_tensors;
}

static std::vector<at::OptionalTensorRef> get_unboxed_opt_tensor_vector() {
  std::vector<at::OptionalTensorRef> optional_tensors;
  const size_t SIZE = 5;
  for (size_t i = 0; i < SIZE * 2; i++) {
    auto opt_tensor = (i % 2 == 0) ? at::OptionalTensorRef(at::empty({0}))
                                   : at::OptionalTensorRef();
    optional_tensors.emplace_back(opt_tensor);
  }
  return optional_tensors;
}

template <typename T>
void check_elements_same(at::ITensorListRef list, const T& thing, int use_count) {
  EXPECT_EQ(thing.size(), list.size());
  size_t i = 0;
  for (const auto& t : list) {
    const at::Tensor& other = thing[i];
    EXPECT_EQ(other.use_count(), use_count);
    EXPECT_TRUE(other.is_same(t));
    i++;
  }
}

TEST(ITensorListRefTest, CtorEmpty_IsNone_Throws) {
  at::ITensorListRef list;
  EXPECT_TRUE(list.isNone());
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto,hicpp-avoid-goto)
  EXPECT_THROW(list.size(), c10::Error);
}

TEST(ITensorListRefTest, CtorBoxed_IsBoxed) {
  auto vec = get_tensor_vector();
  List<at::Tensor> boxed(vec);
  at::ITensorListRef list(boxed);
  EXPECT_TRUE(list.isBoxed());
}

TEST(ITensorListRefTest, CtorUnboxed_IsUnboxed) {
  auto vec = get_tensor_vector();
  at::ArrayRef<at::Tensor> unboxed(vec);
  at::ITensorListRef list(unboxed);
  EXPECT_TRUE(list.isUnboxed());
}

TEST(ITensorListRefTest, CtorUnboxedIndirect_IsUnboxed) {
  auto vec = get_tensor_vector();
  auto check_is_unboxed = [](at::ITensorListRef list) {
    EXPECT_TRUE(list.isUnboxed());
  };
  check_is_unboxed(at::ITensorListRef{vec[0]});
  check_is_unboxed(at::ITensorListRef{vec.data(), vec.size()});
  check_is_unboxed(at::ITensorListRef{&*vec.begin(), &*vec.end()});
  check_is_unboxed(vec);
  check_is_unboxed({vec[0], vec[1], vec[2]});
}

TEST(ITensorListRefTest, CtorTemp_IsUnboxed) {
  auto check_is_unboxed = [](at::ITensorListRef list) {
    EXPECT_TRUE(list.isUnboxed());
  };

  auto vec = get_tensor_vector();
  check_is_unboxed({vec[0], vec[1]});
}

TEST(ITensorListRefTest, Boxed_GetConstRefTensor) {
  auto vec = get_tensor_vector();
  // We need 'boxed' to be 'const' here (and some other tests below)
  // because 'List<Tensor>::operator[]' returns a 'ListElementReference'
  // instead of returning a 'Tensor'. On the other hand,
  // 'List<Tensor>::operator[] const' returns a 'const Tensor &'.
  const List<at::Tensor> boxed(vec);
  at::ITensorListRef list(boxed);
  static_assert(
      std::is_same<decltype(*list.begin()), const at::Tensor&>::value,
      "Accessing elements from List<Tensor> through a ITensorListRef should be const references.");
  EXPECT_TRUE(boxed[0].is_same(*list.begin()));
  EXPECT_TRUE(boxed[1].is_same(*(++list.begin())));
}

TEST(ITensorListRefTest, Unboxed_GetConstRefTensor) {
  auto vec = get_tensor_vector();
  at::ITensorListRef list(vec);
  static_assert(
      std::is_same<decltype(*list.begin()), const at::Tensor&>::value,
      "Accessing elements from ArrayRef<Tensor> through a ITensorListRef should be const references.");
  EXPECT_TRUE(vec[0].is_same(*list.begin()));
  EXPECT_TRUE(vec[1].is_same(*(++list.begin())));
}

TEST(ITensorListRefTest, Boxed_Equal) {
  auto vec = get_tensor_vector();
  List<at::Tensor> boxed(vec);
  check_elements_same(boxed, vec, /* use_count= */ 2);
}

TEST(ITensorListRefTest, Unboxed_Equal) {
  auto vec = get_tensor_vector();
  check_elements_same(at::ArrayRef<at::Tensor>(vec), vec, /* use_count= */ 1);
}

TEST(ITensorListRefTest, UnboxedIndirect_Equal) {
  // The 4 ref-count locations:
  //   1. `vec`
  //   2. `initializer_list` for `ITensorListRef`
  //   3. `initializer_list` for `std::vector`
  //   4. temporary `std::vector`
  auto vec = get_tensor_vector();
  // Implicit constructors
  check_elements_same(vec[0], std::vector<at::Tensor>{vec[0]}, /* use_count= */ 3);
  check_elements_same({vec.data(), vec.size()}, vec, /* use_count= */ 1);
  check_elements_same({&*vec.begin(), &*vec.end()}, vec, /* use_count= */ 1);
  // Vector constructor
  check_elements_same(vec, vec, /* use_count= */ 1);
  // InitializerList constructor
  check_elements_same({vec[0], vec[1], vec[2]}, std::vector<at::Tensor>{vec[0], vec[1], vec[2]}, /* use_count= */ 4);
}

TEST(ITensorListRefTest, BoxedMaterialize_Equal) {
  auto vec = get_tensor_vector();
  List<at::Tensor> boxed(vec);
  at::ITensorListRef list(boxed);
  auto materialized = list.materialize();
  check_elements_same(list, vec, 2);
  check_elements_same(list, materialized, 2);
  check_elements_same(materialized, vec, 2);
}

TEST(ITensorListRefTest, UnboxedMaterialize_Equal) {
  auto vec = get_tensor_vector();
  at::ArrayRef<at::Tensor> unboxed(vec);
  at::ITensorListRef list(unboxed);
  auto materialized = list.materialize();
  check_elements_same(list, vec, 1);
  check_elements_same(list, materialized, 1);
  check_elements_same(materialized, vec, 1);
}

TEST(ITensorListRefIteratorTest, CtorEmpty_ThrowsError) {
  at::ITensorListRefIterator it;
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto,hicpp-avoid-goto)
  EXPECT_THROW(*it, c10::Error);
}

TEST(ITensorListRefIteratorTest, Boxed_GetFirstElement) {
  auto vec = get_tensor_vector();
  const List<at::Tensor> boxed(vec);
  at::ITensorListRef list(boxed);
  EXPECT_TRUE(boxed[0].is_same(*list.begin()));
}

TEST(ITensorListRefIteratorTest, Unboxed_GetFirstElement) {
  auto vec = get_tensor_vector();
  at::ITensorListRef list(vec);
  EXPECT_TRUE(vec[0].is_same(*list.begin()));
}

TEST(ITensorListRefIteratorTest, Boxed_Equality) {
  auto vec = get_tensor_vector();
  List<at::Tensor> boxed(vec);
  at::ITensorListRef list(boxed);
  EXPECT_EQ(list.begin(), list.begin());
  EXPECT_NE(list.begin(), list.end());
  EXPECT_NE(list.end(), list.begin());
  EXPECT_EQ(list.end(), list.end());
}

TEST(ITensorListRefIteratorTest, Unboxed_Equality) {
  auto vec = get_tensor_vector();
  at::ITensorListRef list(vec);
  EXPECT_EQ(list.begin(), list.begin());
  EXPECT_NE(list.begin(), list.end());
  EXPECT_NE(list.end(), list.begin());
  EXPECT_EQ(list.end(), list.end());
}

TEST(ITensorListRefIteratorTest, Boxed_Iterate) {
  auto vec = get_tensor_vector();
  const List<at::Tensor> boxed(vec);
  at::ITensorListRef list(boxed);
  size_t i = 0;
  for (const auto& t : list) {
    EXPECT_TRUE(boxed[i++].is_same(t));
  }
  EXPECT_EQ(i, list.size());
}

TEST(ITensorListRefIteratorTest, Unboxed_Iterate) {
  auto vec = get_tensor_vector();
  at::ITensorListRef list(vec);
  size_t i = 0;
  for (const auto& t : list) {
    EXPECT_TRUE(vec[i++].is_same(t));
  }
  EXPECT_EQ(i, list.size());
}

TEST(IOptTensorListRefTest, Boxed_Iterate) {
  auto vec = get_boxed_opt_tensor_vector();
  const List<optional<at::Tensor>> boxed(vec);
  at::IOptTensorListRef list(boxed);
  size_t i = 0;
  for (const auto t : list) {
    EXPECT_EQ(boxed[i].has_value(), t.has_value());
    if (t.has_value()) {
      EXPECT_TRUE((*boxed[i]).is_same(*t));
    }
    i++;
  }
  EXPECT_EQ(i, list.size());
}

TEST(IOptTensorListRefTest, Unboxed_Iterate) {
  auto vec = get_unboxed_opt_tensor_vector();
  at::ArrayRef<at::OptionalTensorRef> unboxed(vec);
  at::IOptTensorListRef list(unboxed);
  size_t i = 0;
  for (const auto t : list) {
    EXPECT_EQ(unboxed[i].has_value(), t.has_value());
    if (t.has_value()) {
      EXPECT_TRUE((*unboxed[i]).is_same(*t));
    }
    i++;
  }
  EXPECT_EQ(i, list.size());
}
