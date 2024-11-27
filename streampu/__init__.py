# -*- coding: utf-8 -*-
r"""StreamPU package.

The streampu package provides interfaces for the StreamPU C++ library.
"""

# Stack of hidden modules
_mdl_stack = []

# Tools
from streampu._ext import FormatFlags, Signal_handler, exceptions, help

# Modules with no factory
from streampu._ext.ada import Adaptor, Adaptor_1_to_n, Adaptor_n_to_1
from streampu._ext.ctl import (
    Controller,
    Controller_cyclic,
    Controller_limit,
    Controller_static,
)
from streampu._ext.interfaces import (
    Interface_clone,
    Interface_get_set_n_frames,
    Interface_is_done,
    Interface_reset,
    Interface_set_seed,
    Interface_waiting,
)
from streampu._ext.ite import Iterator
from streampu._ext.ran import Range
from streampu._ext.reporter import Reporter, Reporter_probe
from streampu._ext.set import Set
from streampu._ext.slp import Sleeper
from streampu._ext.swi import Switcher
from streampu._ext.terminal import Terminal, Terminal_dump, Terminal_std

from . import rang

# array is required for some socket features
from ._array import arange, array, ones, zeros

# Modules with factory
from ._bop import (
    BType,
    add,
    bitwise_and,
    bitwise_or,
    bitwise_xor,
    bop,
    div,
    equal,
    greater,
    greater_equal,
    less,
    less_equal,
    mul,
    not_equal,
    sub,
)
from ._delayer import delayer
from ._dtype import (
    dtype,
    float32,
    float64,
    int8,
    int16,
    int32,
    int64,
    uint8,
    uint16,
    uint32,
    uint64,
)
from ._finalizer import finalizer
from ._incrementer import incrementer
from ._initializer import initializer

# Proxies for min and max
from ._minmax import max, min
from ._module import Module
from ._pipeline import Pipeline
from ._probe import (
    AProbe,
    Probe_latency,
    Probe_occurrence,
    Probe_throughput,
    Probe_time,
    Probe_timestamp,
    probe_value,
)
from ._red import RType, all, any, prod, red, sum
from ._relayer import relayer
from ._sequence import Sequence
from ._sink import sink_no, sink_user_binary

# Core
from ._socket import Socket
from ._source import source_random, source_user, source_user_binary
from ._stateless import Stateless
from ._task import Task
from ._uop import UType, abs, bitwise_not, cast, neg, uop
from ._version import version as __version__
