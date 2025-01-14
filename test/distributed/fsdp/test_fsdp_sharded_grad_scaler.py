# Owner(s): ["oncall: distributed"]

import functools
import itertools
import sys
import torch
import unittest

from torch import distributed as dist
from torch.cuda.amp.common import amp_definitely_not_available
from torch.distributed.fsdp.fully_sharded_data_parallel import ShardingStrategy
from torch.distributed.fsdp import MixedPrecision, CPUOffload
from torch.distributed.fsdp.sharded_grad_scaler import ShardedGradScaler
from torch.testing._internal.common_fsdp import DummyProcessGroup, subtest_name, FSDPInitMode, NestedWrappedModule, FSDPTest
from torch.testing._internal.common_distributed import skip_if_lt_x_gpu
from torch.testing._internal.common_utils import (
    TestCase, run_tests,
    instantiate_parametrized_tests,
    parametrize,
    TEST_WITH_DEV_DBG_ASAN,
)


if not dist.is_available():
    print("Distributed not available, skipping tests", file=sys.stderr)
    sys.exit(0)


if TEST_WITH_DEV_DBG_ASAN:
    print(
        "Skip dev-asan as torch + multiprocessing spawn have known issues",
        file=sys.stderr,
    )
    sys.exit(0)


params = "cpu_offload,sharding_strategy,mixed_precision"
cpu_offload_config = [CPUOffload(offload_params=True), CPUOffload(offload_params=False)]
sharding_strategy_config = [ShardingStrategy.SHARD_GRAD_OP, None]
mixed_precision = ["enable_mixed_precision", None]

configs = list(itertools.product(cpu_offload_config,
                                 sharding_strategy_config,
                                 mixed_precision))
test_name_mapping = {
    str(CPUOffload(offload_params=True)): "offload_true",
    str(CPUOffload(offload_params=False)): "offload_false",
    str(ShardingStrategy.SHARD_GRAD_OP): "shard_grad_op",
    "enable_mixed_precision": "mixed_precision"
}

subtest_name = functools.partial(subtest_name, test_name_mapping)


class TestShardGradScaler(TestCase):
    @unittest.skipIf(amp_definitely_not_available(), "no supported device (cuda, xla) found")
    def test_grad_scaling(self):
        pg = DummyProcessGroup(0, 1)
        scaler = ShardedGradScaler(init_scale=2.0, process_group=pg, enabled=True)
        t0 = torch.full((1,), 4.0, dtype=torch.float32, device="cpu")
        t1 = torch.full((1,), 8.0, dtype=torch.float32, device="cpu")
        outputs = [t1.clone(), (t0.clone(), t1.clone()), [t0.clone(), t1.clone()]]
        outputs = scaler.scale(outputs)
        self.assertTrue(outputs[0] == 16.0 and outputs[1][0] == 8.0 and outputs[1][1] == 16.0)
        self.assertTrue(outputs[2][0] == 8.0 and outputs[2][1] == 16.0)
        self.assertTrue(scaler._scale.device == t1.device)

    @unittest.skipIf(amp_definitely_not_available(), "no supported device (cuda, xla) found")
    def test_scaling_unscaling_sparse(self):
        pg = DummyProcessGroup(0, 1)
        scaler = ShardedGradScaler(init_scale=2.0, process_group=pg, enabled=True)
        inv_scale = torch.full((1,), 0.5, dtype=torch.float, device="cpu")
        found_inf = torch.full((1,), 0, dtype=torch.float, device="cpu")

        i = torch.tensor([[0, 1, 1],
                          [2, 0, 2]], device="cpu", dtype=torch.int64)
        v = torch.tensor([16.0, 32.0, 64.0], dtype=torch.float, device="cpu")
        s = torch.sparse_coo_tensor(i, v, torch.Size([2, 3]), device="cpu", dtype=torch.float)

        # unscale sparse tensors
        s1 = s.clone()
        s1.grad = s.clone()
        opt = torch.optim.SGD([s1], lr=1.0)
        found_inf.zero_()
        found_inf = scaler._unscale_grads_(opt, inv_scale, found_inf)[s1.device]
        self.assertEqual(found_inf, 0.0)
        self.assertEqual(s1.grad.to_dense(), (s / 2).to_dense())

        # unscale sparse tensor: inf
        v = torch.tensor([16.0, 32.0, float('inf')], dtype=torch.float, device="cpu")
        s1.grad = torch.sparse_coo_tensor(i, v, torch.Size([2, 3]), device="cpu", dtype=torch.float)
        found_inf.zero_()
        found_inf = scaler._unscale_grads_(opt, inv_scale, found_inf)[s1.device]
        self.assertEqual(found_inf, 1.0)

        # unscale sparse tensor: overflow (marked as inf)
        i = torch.tensor([[1, 1, 1],
                          [0, 0, 2]], device="cpu", dtype=torch.int64)
        # coalescing sparse tensor here will cause the value to be Inf
        v = torch.tensor([2**15, 2**15, 1.0], dtype=torch.float16, device="cpu")
        s1 = torch.sparse_coo_tensor(i, v, torch.Size([2, 3]), device="cpu", dtype=torch.float16)
        s1.grad = s1.clone()
        found_inf.zero_()
        found_inf = scaler._unscale_grads_(opt, inv_scale, found_inf)[s1.device]
        self.assertEqual(found_inf, 1.0)

    @unittest.skipIf(amp_definitely_not_available(), "no supported device (cuda, xla) found")
    def test_inf_gradients_skip_optim_step(self):
        pg = DummyProcessGroup(0, 1)
        scaler = ShardedGradScaler(init_scale=2.0, process_group=pg, enabled=True)
        loss = torch.full((1,), 4.0, dtype=torch.float32, device="cpu")
        t0 = torch.tensor([float('inf')], dtype=torch.float32, device="cpu")
        t0.grad = t0.clone()
        opt = torch.optim.SGD([t0], lr=1.0)
        scaler.scale(loss)
        ret_val = scaler.step(opt)
        self.assertTrue(ret_val is None)


class TestShardedGradScalerParityWithDDP(FSDPTest):
    def _get_init_modes_for_test(self, cpu_offload):
        modes = [
            FSDPInitMode.CUDA_AFTER,
            FSDPInitMode.CUDA_BEFORE
        ]
        # Note that FSDPInitMode.CUDA_NEVER works currently only with CPU
        # offload as we explicitly bring the param back to CUDA device. In
        # general, it will not work since we try to all_gather p.data which is
        # on CPU but NCCL only supports GPU.
        if cpu_offload.offload_params:
            modes.append(FSDPInitMode.CUDA_NEVER)

        return modes

    @skip_if_lt_x_gpu(2)
    @parametrize(params, configs, subtest_name)
    def test_scaler_enabled(self, cpu_offload, sharding_strategy, mixed_precision):
        init_modes = self._get_init_modes_for_test(cpu_offload)
        mp = MixedPrecision(
            param_dtype=torch.float16,
            reduce_dtype=torch.float16,
            buffer_dtype=torch.float16,
        ) if mixed_precision else None
        for fsdp_init_mode in init_modes:
            self._test_identical_outputs(
                NestedWrappedModule,
                fsdp_init_mode=fsdp_init_mode,
                cpu_offload=cpu_offload,
                sharding_strategy=sharding_strategy,
                mixed_precision=mp,
                enable_sharded_grad_scaler=True,
            )


instantiate_parametrized_tests(TestShardGradScaler)
instantiate_parametrized_tests(TestShardedGradScalerParityWithDDP)

if __name__ == "__main__":
    run_tests()
