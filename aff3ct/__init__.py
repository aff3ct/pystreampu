r"""
The aff3ct package provides interfaces for C++ Module Task and Socket classes
of the AFF3CT library.
"""
from __future__ import annotations

from aff3ct._ext import help as _help
from aff3ct._ext import Range as _range
from aff3ct._ext import exceptions as _exceptions

exceptions = _exceptions
help  = _help
range = _range

from ._array  import *

from ._dtype  import (dtype, uint8, uint16, uint32, uint64, int8,
                      int16, int32, int64, float32, float64)

from ._socket import Socket
from ._task   import Task
from ._module import Module

from ._bop import (BType, bop, add, sub, mul, div, greater_equal, greater,
                   equal, not_equal, less_equal, less, bitwise_and, bitwise_or,
                   bitwise_xor)

from ._bop import min as bop_min
from ._bop import max as bop_max

from ._uop import *
from ._red import (RType, red, sum, prod, all, any)
from ._red import min as red_min, max as red_max

from ._stateless import Stateless

def min(s_0: Socket,
        *args: tuple[Socket, ...],
        output_dtype: dtype = None) -> Socket:

    if len(args) == 0:
        return red_min(s_0, output_dtype=output_dtype)

    min_ = s_0
    for arg in args:
        min_ = bop_min(min_, arg, output_dtype=output_dtype)
    return min_


def max(s_0: Socket,
        *args: tuple[Socket, ...],
        output_dtype: dtype = None) -> Socket:

    if len(args) == 0:
        return red_max(s_0, output_dtype=output_dtype)

    max_ = s_0
    for arg in args:
        max_ = bop_max(max_, arg, output_dtype=output_dtype)
    return max_


from ._uop    import *

from ._sequence import *