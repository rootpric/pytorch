#pragma once

#include <torch/csrc/jit/ir/ir.h>
#include <mutex>
#include <unordered_map>

namespace torch {
namespace jit {

class ConstantValueMap {
 public:
  static ConstantValueMap& getInstance();

  static void SetRank(const std::string& tensorName, size_t rankValue);
  static bool HasRank(const std::string& tensorName);
  static c10::optional<size_t> GetRank(const std::string& tensorName);

  static void SetShape(
      const std::string& tensorName,
      const c10::SymbolicShape& shapeValue);
  static bool HasShape(const std::string& tensorName);
  static c10::optional<c10::SymbolicShape> GetShape(
      const std::string& tensorName);

  static void SetValue(const std::string& tensorName, const at::Tensor& value);
  static bool HasValue(const std::string& tensorName);
  static c10::optional<at::Tensor> GetValue(const std::string& tensorName);

  static std::vector<int64_t> GetCompleteShapeInto1DInt64Vector(
      const c10::SymbolicShape& shape);
  static c10::optional<std::vector<int64_t>> GetShapeInto1DInt64Vector(
      const std::string& value_name);
  static c10::optional<std::vector<int64_t>>
  GetShapeInto1DInt64VectorWithOneUnknown(const std::string& value_name);
  static std::vector<int64_t> GetValueInto1DInt64Vector(
      const std::string& value_name);

  static void SetTypeReliable(const std::string& tensorName, bool reliable);
  static bool HasTypeReliable(const std::string& tensorName);
  static c10::optional<bool> GetTypeReliable(const std::string& tensorName);

  static void SetUseInferredType(
      const std::string& tensorName,
      bool useInferredType);
  static bool HasUseInferredType(const std::string& tensorName);
  static c10::optional<bool> GetUseInferredType(const std::string& tensorName);

  static void SetShapeValue(
      const std::string& tensorName,
      const c10::SymbolicShape& shapeValue);
  static bool HasShapeValue(const std::string& tensorName);
  static c10::optional<c10::SymbolicShape> GetShapeValue(
      const std::string& tensorName);

  static void UpdateValueName(
      const std::string& old_name,
      const std::string& new_name);

  static void PrintMaps();
  static void ClearMaps();
  ~ConstantValueMap() = default;

  ConstantValueMap& operator=(const ConstantValueMap&) = delete;

 private:
  ConstantValueMap() = default;

  std::unordered_map<std::string, size_t> rankMap;
  std::unordered_map<std::string, c10::SymbolicShape> shapeMap;
  std::unordered_map<std::string, at::Tensor> tensorValueMap;
  // This map indicates whether the current type is reliably estimated or not.
  std::unordered_map<std::string, bool> typeReliableMap;
  // This map indicates whether the current type is estimated through inference
  // or tracer.
  std::unordered_map<std::string, bool> useInferredTypeMap;
  // This map indicates a tensor value which represents a shape.
  // We assume that the rank of the tensor value <= 1, and we ensure this when
  // we write the processing logic for the operators. When the rank > 1, we
  // should be able to rewrite the model so that the rank <= 1. The difference
  // between shapeMap and shapeValueMap: shapeMap stores the shape of the tensor
  // from a node. shapeValueMap stores the value of the tensor from a node when
  // this tensor represents a shape.
  std::unordered_map<std::string, c10::SymbolicShape> shapeValueMap;
};

} // namespace jit
} // namespace torch
