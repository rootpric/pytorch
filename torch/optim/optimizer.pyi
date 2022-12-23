from typing import Iterable, Union, Callable, Optional, List
from .. import Tensor

_params_t = Union[Iterable[Tensor], Iterable[dict]]


class Optimizer:
    defaults: dict
    state: dict
    param_groups: List[dict]

    def __init__(self, params: _params_t, default: dict) -> None: ...
    def __setstate__(self, state: dict) -> None: ...
    def state_dict(self) -> dict: ...
    def load_state_dict(self, state_dict: dict) -> None: ...
    def zero_grad(self, set_to_none: bool=...) -> None: ...
    def step(self, closure: Optional[Callable[[], float]]=...) -> Optional[float]: ...
    def add_param_group(self, param_group: dict) -> None: ...
