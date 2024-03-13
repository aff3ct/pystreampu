r"""
The aff3ct package provides interfaces for C++ Module Task and Socket classes
of the AFF3CT library.
"""
from __future__ import annotations


from ._dtype  import (dtype, uint8, uint16, uint32, uint64, int8,
                      int16, int32, int64, float32, float64)

from ._module import Module

# array is required for some socket features
from ._array  import *

# Core
from ._socket import Socket
from ._task import Task
from ._sequence import Sequence

# Tools
from aff3ct._ext import exceptions
from aff3ct._ext import help
from aff3ct._ext.interfaces import *
from aff3ct._ext import help, Range, exceptions, disable_colors, enable_colors
from aff3ct._ext.terminal import Terminal, Terminal_dump, Terminal_std
from aff3ct._ext import fmtflags as FormatFlags
from . import rang

# Modules with no factory
from aff3ct._ext.ite import Iterator
from aff3ct._ext.ran import Range
from aff3ct._ext.slp import Sleeper
from aff3ct._ext.sse import Subsequence
from aff3ct._ext.swi import Switcher

# Modules with factory
from ._bop import (BType, bop, add, sub, mul, div, greater_equal, greater,
                   equal, not_equal, less_equal, less, bitwise_and, bitwise_or,
                   bitwise_xor)
from ._delayer import *
from ._finalizer import *
from ._initializer import *
from ._incrementer import *
from ._probe import *
from ._red import RType, red, sum, prod, all, any
from ._relayer import *
from ._reporter import *
from ._source import *
from ._stateless import Stateless
from ._uop import *

# Proxies for min and max
from ._minmax import min, max