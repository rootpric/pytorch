#include <gtest/gtest.h>

#include <test/cpp/jit/test_utils.h>
#include <torch/csrc/jit/ir/irparser.h>

namespace torch {
namespace jit {

TEST(IRTest, Attributes) {
  Graph g;
  auto one = attr::alpha;
  auto two = attr::device;
  auto three = attr::end;
  auto four = attr::perm;
  Node* n = g.create(Symbol::fromQualString("foo::bar"));
  Node& attr = *n;
  attr.f_(one, 3.4)->i_(two, 5)->s_(three, "what");
  ASSERT_EQ(attr.f(one), 3.4);
  ASSERT_EQ(attr.s(three), "what");
  ASSERT_EQ(attr.i(two), 5);
  attr.s_(one, "no");
  ASSERT_EQ(attr.s(one), "no");
  ASSERT_TRUE(attr.hasAttribute(three));
  ASSERT_TRUE(!attr.hasAttribute(four));
  attr.ss_(two, {"hi", "now"});
  ASSERT_EQ(attr.ss(two).at(1), "now");

  Node* n2 = g.create(Symbol::fromQualString("foo::baz"));
  Node& attr2 = *n2;
  attr2.copyAttributes(attr);
  ASSERT_EQ(attr2.s(one), "no");
  attr2.f_(one, 5);
  ASSERT_EQ(attr.s(one), "no");
  ASSERT_EQ(attr2.f(one), 5);
}

TEST(IRTest, Blocks) {
  auto g = std::make_shared<Graph>();
  const auto graph_string = R"IR(
    graph(%a : Tensor,
          %b : Tensor,
          %c : Tensor):
      %2 : int = prim::Constant[value=1]()
      %3 : Tensor = aten::add(%a, %b, %2)
      %5 : Tensor = prim::If(%c)
        block0():
          %6 : int = prim::Constant[value=1]()
          %7 : Tensor = aten::add(%3, %3, %6)
          -> (%7)
        block1():
          %8 : int = prim::Constant[value=1]()
          %9 : Tensor = aten::add(%b, %3, %8)
          %10 : int = prim::Constant[value=1]()
          %11 : Tensor = aten::add(%9, %3, %10)
          -> (%11)
      %12 : int = prim::Constant[value=1]()
      %13 : Tensor = aten::add(%5, %3, %12)
      return (%13))IR";
  torch::jit::parseIR(graph_string, g.get());

  g->lint();
  testing::FileCheck()
      .check("add")
      ->check("prim::If")
      ->check("block0")
      ->check("aten::add")
      ->check("block1")
      ->check_count("aten::add", 3)
      ->run(*g);

  // Removes block0 of the conditional
  for (auto* node : g->block()->nodes()) {
    if (node->kind() == prim::If) {
      node->eraseBlock(0);
      break;
    }
  }

  testing::FileCheck()
      .check("add")
      ->check("prim::If")
      ->check("block0")
      ->check_not("block")
      ->run(*g);
  g->lint();
  // test recursive copy of blocks works
  auto g2 = g->copy();
  testing::FileCheck()
      .check("add")
      ->check("prim::If")
      ->check("block0")
      ->check_not("block")
      ->run(*g2);
}

TEST(IRTest, CommonAncestor) {
  std::string input_str = R"(
graph(%x : Tensor,
      %a.1 : bool,
      %b.1 : bool,
      %c.1 : bool):
  %4 : int = prim::If(%a.1)
    block0():
      %5 : int = prim::If(%b.1)
        block0():
          %6 : int = prim::Constant[value=2]()
          -> (%6)
        block1():
          %7 : int = prim::Constant[value=3]()
          -> (%7)
      -> (%5)
    block1():
      %8 : int = prim::If(%c.1)
        block0():
          %9 : int = prim::Constant[value=4]()
          -> (%9)
        block1():
          %10 : int = prim::Constant[value=5]()
          -> (%10)
      -> (%8)
  return (%4)
)";

  torch::jit::Graph g;
  std::unordered_map<std::string, torch::jit::Value*> name_to_value;
  torch::jit::parseIR(input_str, &g, name_to_value);

  std::vector<std::string> value_names{"6", "7", "9", "10"};
  std::unordered_set<std::string> value_names_set(
      value_names.begin(), value_names.end());

  /* clang-format off */
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
  int ref_blocks_from_graph[4][4] = {
    /* (6, 6), (6, 7), (6, 9), (6, 10) */
    {   2,     1,      0,      0        },
    /* (7, 6), (7, 7), (7, 9), (7, 10) */
    {   1,     2,      0,      0        },
    /* (9, 6), (9, 7), (9, 9), (9, 10) */
    {   0,     0,      2,      1,       },
    /* (10, 6),(10, 7),(10, 9),(10, 10) */
    {   0,     0,      1,      2        }
  };
  /* clang-format on */

  for (size_t i = 0; i < value_names.size(); ++i) {
    Value* i_val = name_to_value[value_names[i]];
    for (size_t j = 0; j < value_names.size(); ++j) {
      Value* j_val = name_to_value[value_names[j]];
      Block* common_ancestor =
          i_val->node()->findCommonAncestorBlockWith(j_val->node());
      int blocks_from_graph_block =
          common_ancestor->param_node()->blocksFromGraphBlock();
      ASSERT_EQ(blocks_from_graph_block, ref_blocks_from_graph[i][j]);
    }
  }
}

TEST(IRTest, OperatorMap) {
  OperatorMap<int> op_map;
  const char* literal1 =
      "aten::dropout(Tensor input, float p, bool train) -> Tensor";
  const char* literal2 =
      "aten::bernoulli(Tensor self, *, Generator? generator) -> Tensor";
  const char* literal3 =
      "aten::bernoulli(Tensor self, float p, *, Generator? generator) -> Tensor";
  const char* literal4 =
      "aten::normal(Tensor mean, Tensor std, *, Generator? generator) -> Tensor";
  const char* literal5 =
      "aten::normal(float mean, Tensor std, *, Generator? generator) -> Tensor";
  const char* literal6 =
      "aten::normal(Tensor mean, float std, *, Generator? generator) -> Tensor";
  std::shared_ptr<Operator> op1 = getOperatorForLiteral(literal1);
  std::shared_ptr<Operator> op2 = getOperatorForLiteral(literal2);
  std::shared_ptr<Operator> op3 = getOperatorForLiteral(literal3);
  std::shared_ptr<Operator> op4 = getOperatorForLiteral(literal4);
  std::shared_ptr<Operator> op5 = getOperatorForLiteral(literal5);
  std::shared_ptr<Operator> op6 = getOperatorForLiteral(literal6);
  op_map.insert(op1, 1);
  op_map.insert({{op2, 2}, {op3, 3}});
  op_map.insert({{op4, 4}, {op5, 5}});
  op_map.insert(op6, 6);
  ASSERT_TRUE(op_map.contains(*op1));
  ASSERT_TRUE(op_map.contains(*op2));
  ASSERT_TRUE(op_map.contains(*op3));
  ASSERT_TRUE(op_map.contains(*op4));
  ASSERT_TRUE(op_map.contains(*op5));
  ASSERT_TRUE(op_map.contains(*op6));
  op_map.erase(op6);
  op_map.erase(op3);
  op_map.erase(op1);
  ASSERT_FALSE(op_map.contains(*op1));
  ASSERT_FALSE(op_map.contains(*op3));
  ASSERT_FALSE(op_map.contains(*op6));
  op_map.insert(op1, 1);
  ASSERT_TRUE(op_map.contains(*op1));
  c10::optional<int> o1 = op_map.find(*op1);
  ASSERT_TRUE(o1.has_value());
  c10::optional<int> o2 = op_map.find(*op2);
  ASSERT_TRUE(o2.has_value());
  c10::optional<int> o3 = op_map.find(*op3);
  ASSERT_FALSE(o3.has_value());
  c10::optional<int> o4 = op_map.find(*op4);
  ASSERT_TRUE(o4.has_value());
  c10::optional<int> o5 = op_map.find(*op5);
  ASSERT_TRUE(o5.has_value());
  c10::optional<int> o6 = op_map.find(*op6);
  ASSERT_FALSE(o6.has_value());
}

} // namespace jit
} // namespace torch
