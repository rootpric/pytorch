#pragma once

#include <torch/csrc/jit/ir/ir.h>

namespace torch {
namespace jit {

TORCH_API void RemoveRedundantProfiles(std::shared_ptr<Graph>& graph);
TORCH_API void RemoveRedundantProfiles(Block* block, AliasDb& db);
} // namespace jit
} // namespace torch
