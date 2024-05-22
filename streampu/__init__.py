r"""
The streampu package provides interfaces for C++ Module Task and Socket classes
of the StreamPU library.
"""

from __future__ import annotations


from ._dtype import (
    dtype,
    uint8,
    uint16,
    uint32,
    uint64,
    int8,
    int16,
    int32,
    int64,
    float32,
    float64,
)

from ._module import Module

# array is required for some socket features
from ._array import *

# Core
from ._socket import Socket
from ._task import Task
from ._sequence import Sequence
from ._pipeline import Pipeline

# Tools
from streampu._ext import Signal_handler
from streampu._ext import exceptions
from streampu._ext import help
from streampu._ext.interfaces import *
from streampu._ext.terminal import Terminal, Terminal_dump, Terminal_std
from streampu._ext import fmtflags as FormatFlags
from . import rang

# Modules with no factory
from streampu._ext.ada import *
from streampu._ext.ctl import *
from streampu._ext.ite import Iterator
from streampu._ext.ran import Range
from streampu._ext.slp import Sleeper
from streampu._ext.set import Set
from streampu._ext.swi import Switcher

# Modules with factory
from ._bop import (
    BType,
    bop,
    add,
    sub,
    mul,
    div,
    greater_equal,
    greater,
    equal,
    not_equal,
    less_equal,
    less,
    bitwise_and,
    bitwise_or,
    bitwise_xor,
)
from ._delayer import *
from ._finalizer import *
from ._initializer import *
from ._incrementer import *
from ._probe import *
from ._red import RType, red, sum, prod, all, any
from ._relayer import *
from ._reporter import *
from ._sink import *
from ._source import *
from ._stateless import Stateless
from ._uop import *

# Proxies for min and max
from ._minmax import min, max
