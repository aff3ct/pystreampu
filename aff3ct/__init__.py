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
from ._task import Task
from ._module import Module
from aff3ct._ext import help, Range, exceptions, disable_colors, enable_colors
from aff3ct._ext.terminal import Terminal, Terminal_dump, Terminal_std
from aff3ct._ext.sse import Subsequence
from aff3ct._ext import fmtflags as FormatFlags
from aff3ct._ext.interfaces import *
from aff3ct._ext.swi import *
from aff3ct._ext.ini import *
from ._bop import (BType, bop, add, sub, mul, div, greater_equal, greater,
                   equal, not_equal, less_equal, less, bitwise_and, bitwise_or,
                   bitwise_xor)
from ._uop import *
from ._red import RType, red, sum, prod, all, any
from ._minmax import min, max
from ._probe import *
from ._stateless import Stateless
from ._uop import *
from ._sequence import *
from ._source import *
from ._delayer import *
from ._reporter import *
from ._finalizer import *
from ._initializer import *
from ._incrementer import *
from . import rang
