#include <ATen/Functions.h>
#include <gtest/gtest.h>
#include <torch/csrc/jit/backends/backend.h>
#include <torch/csrc/jit/backends/backend_detail.h>
#include <torch/csrc/jit/backends/backend_preprocess.h>
#include <torch/csrc/jit/frontend/resolver.h>
#include <torch/csrc/jit/mobile/import.h>
#include <torch/csrc/jit/mobile/module.h>
#include <torch/csrc/jit/mobile/nnc/context.h>
#include <torch/csrc/jit/mobile/nnc/registry.h>
#include <torch/csrc/jit/passes/freeze_module.h>
#include <torch/custom_class.h>
#include <torch/script.h>

namespace torch {
namespace jit {
namespace mobile {
namespace nnc {

namespace {

c10::Dict<c10::IValue, c10::IValue> create_compile_spec(
    const std::string& method_name,
    const std::string& model_name,
    const std::string& input_shapes,
    const std::string& input_types,
    const std::string& memory_formats,
    const std::string& dynamic_sizes) {
  c10::Dict<c10::IValue, c10::IValue> method_spec(
      c10::StringType::get(), c10::AnyType::get());

  method_spec.insert("sizes", input_shapes);
  method_spec.insert("types", input_types);
  method_spec.insert("model_name", model_name);
  method_spec.insert("model_version", "v1");
  method_spec.insert("asmfile", "fake_nnc_model.s");
  method_spec.insert("arch", "x86-64");
  method_spec.insert("memory_formats", memory_formats);
  method_spec.insert("dynamic_sizes", dynamic_sizes);

  c10::Dict<c10::IValue, c10::IValue> compile_spec(
      c10::StringType::get(), c10::AnyType::get());
  compile_spec.insert(method_name, method_spec);
  return compile_spec;
}

} // namespace

extern "C" {

// The test kernels are supposed to be generated by the NNC compiler ahead-of-
// time. For integration test purpose we manually wrote instead.
int add_kernel(void** args) {
  // out = input + param
  at::Tensor input = at::from_blob(args[0], {4, 4}, at::kFloat);
  at::Tensor out = at::from_blob(args[1], {4, 4}, at::kFloat);
  at::Tensor param = at::from_blob(args[2], {1}, at::kFloat);
  out.copy_(at::add(input, param));
  return 0;
}

} // extern "C"

REGISTER_NNC_KERNEL(
    "_add_kernel_nnc_fake_model:v1:forward:VERTOKEN",
    add_kernel)

TEST(NNCBackendTest, AOTCompileThenExecute) {
  torch::jit::Module m("m");
  auto param = torch::ones({1});
  m.register_parameter("param", param, false);
  m.define(R"(
    def forward(self, input):
        return input + self.param
  )");

  // Run the TorchScript module to get reference result.
  std::vector<IValue> inputs;
  inputs.emplace_back(2.0 * torch::ones({4, 4}));
  auto reference = m.forward(inputs);

  // Compile the model with NNC.
  auto compile_spec = create_compile_spec(
      "forward", "_add_kernel_nnc_fake_model", "4,4", "float", "", "");
  auto any_dict_ty =
      c10::DictType::create(c10::StringType::get(), c10::AnyType::get());
  auto frozen_m = torch::jit::freeze_module(m.clone());
  auto compiled_module = torch::jit::detail::codegen_backend_module(
      "nnc", frozen_m, compile_spec, any_dict_ty);

  // Save the compiled model.
  std::stringstream ss;
  compiled_module._save_for_mobile(ss);

  // Load and run the saved model.
  auto loaded_module = _load_for_mobile(ss);
  auto result = loaded_module.forward(inputs);
  EXPECT_TRUE(result.toTensor().equal(3.0 * torch::ones({4, 4})));
  EXPECT_TRUE(result.toTensor().equal(reference.toTensor()));
  EXPECT_EQ(remove("fake_nnc_model.s"), 0);
}

} // namespace nnc
} // namespace mobile
} // namespace jit
} // namespace torch
