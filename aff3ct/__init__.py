from . import builtins
from . import core

help    = builtins.help
range   = builtins.Range
dtype   = builtins.dtype
uint8   = builtins.uint8
uint16  = builtins.uint16
uint32  = builtins.uint32
uint64  = builtins.uint64
int8    = builtins.int8
int16   = builtins.int16
int32   = builtins.int32
int64   = builtins.int64
float32 = builtins.float32
float64 = builtins.float64

from .array.array import *

from .bop.__bop_patch__ import *
from . import bop

from .uop.__uop_patch__ import *
from . import uop

def __dtype_call__(slf, data):
    if type(data) is Socket:
        return data.astype(slf)
    else:
        return array(data, dtype = slf)

dtype.__call__ = lambda slf, data: __dtype_call__(slf, data)

from .jit.jit import *
from .viz.viz import *
