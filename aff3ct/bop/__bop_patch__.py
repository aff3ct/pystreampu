import numpy as np
from .. import builtins
from .. import array
from .Binaryop import Binaryop

def bop_generic_factory(name, s0, s1, invert = False):
    n_frames = 0
    dtype = None
    first = -1
    if type(s0) is builtins.core.Socket and type(s1) is builtins.core.Socket:
        first = -1
        n_frames = s0.task.module.n_frames
        dtype    = s0.dtype

    elif type(s0) is builtins.core.Socket:
        n_frames = s0.task.module.n_frames
        dtype    = s0.dtype
        first    = 0

    elif type(s1) is builtins.core.Socket:
        n_frames = s1.task.module.n_frames
        dtype    = s1.dtype
        first    = 1

    else:
        n_frames = 1
        first    = 0
        np_dtype = np.find_common_type([], [np.array(s0).dtype, np.array(s1).dtype])
        dtype    = builtins.dtype.of(np_dtype.type.__name__)


    if type(s0) is not builtins.core.Socket:
        try:
            s0 = array(np.array(s0, dtype = np.dtype(dtype.name)))
            s0.task.module.n_frames = n_frames
            s0.task.module.get()
        except:
            return NotImplemented
    else:
        mdl0 = s0.task.module

    if type(s1) is not builtins.core.Socket:
        try:
            s1 = array(np.array(s1, dtype = np.dtype(dtype.name)))
            s1.task.module.n_frames = n_frames
            s1.task.module.get()
        except:
            return NotImplemented
    else:
        mdl1 = s1.task.module

    if s0.dtype.name != s1.dtype.name:
        return NotImplemented

    TI = s0.dtype
    TO = TI

    if name in ["eq", "ge", "gt", "le", "lt", "ne"]:
        TO = builtins.int32

    n_in1 = s0.n_elmts//n_frames
    n_in2 = s1.n_elmts//n_frames

    the_bop = Binaryop(n_in1, n_in2, name, TI, TO)
    the_bop.n_frames = s0.task.module.n_frames

    if invert:
        s = the_bop.perform(s1,s0)
    else:
        s = the_bop.perform(s0,s1)

    if first == 1:
        s0.task.bind(s1)
    if first == 0:
        s1.task.bind(s0)
    return s

Socket = builtins.core.Socket

def add (s0, s1): return bop_generic_factory("add",s0,s1)
Socket.__add__  = lambda slf, s : add(slf, s)
Socket.__radd__ = Socket.__add__

def sub  (s0, s1): return bop_generic_factory("sub",s0,s1)
Socket.__sub__  = lambda slf, s : sub(slf, s)
def rsub (s0, s1): return bop_generic_factory("sub",s0,s1,True)
Socket.__rsub__ = lambda slf, s : rsub(slf, s)

def mul (s0, s1): return bop_generic_factory("mul",s0,s1)
Socket.__mul__  = lambda slf, s : mul(slf, s)
Socket.__rmul__ = Socket.__mul__

def div (s0, s1): return bop_generic_factory("div",s0,s1)
Socket.__truediv__  = lambda slf, s : div(slf, s)
def rdiv (s0, s1): return bop_generic_factory("div",s0,s1,True)
Socket.__rtruediv__ = lambda slf, s : rdiv(slf, s)

def greater_equal (s0, s1): return bop_generic_factory("ge",s0,s1)
Socket.__ge__  = lambda slf, s : greater_equal(slf, s)
def rgreater_equal (s0, s1): return bop_generic_factory("ge",s0,s1,True)
Socket.__rge__ = lambda slf, s : rgreater_equal(slf, s)

def greater (s0, s1): return bop_generic_factory("gt",s0,s1)
Socket.__gt__  = lambda slf, s : greater(slf, s)
def rgreater (s0, s1): return bop_generic_factory("gt",s0,s1,True)
Socket.__rgt__  = lambda slf, s : rgreater(slf, s)

def equal (s0, s1): return bop_generic_factory("eq",s0,s1)
Socket.__eq__  = lambda slf, s : equal(slf, s)
Socket.__req__ = Socket.__eq__

def not_equal (s0, s1): return bop_generic_factory("neq",s0,s1)
Socket.__neq__  = lambda slf, s : not_equal(slf, s)
Socket.__rneq__ = Socket.__neq__

def less_equal (s0, s1): return bop_generic_factory("le",s0,s1)
Socket.__le__  = lambda slf, s : less_equal(slf, s)
def rless_equal (s0, s1): return bop_generic_factory("le",s0,s1,True)
Socket.__rle__ = lambda slf, s : rless_equal(slf, s)

def less (s0, s1): return bop_generic_factory("lt",s0,s1)
Socket.__lt__  = lambda slf, s : less(slf, s)
def rless (s0, s1): return bop_generic_factory("lt",s0,s1,True)
Socket.__rlt__ = lambda slf, s : rless(slf, s)

def bitwise_and (s0, s1): return bop_generic_factory("and",s0,s1)
Socket.__and__  = lambda slf, s : bitwise_and(slf, s)
Socket.__rand__ = Socket.__and__

def bitwise_or (s0, s1): return bop_generic_factory("or",s0,s1)
Socket.__or__  = lambda slf, s : bitwise_or(slf, s)
Socket.__ror__ = Socket.__or__

def bitwise_xor (s0, s1): return bop_generic_factory("xor",s0,s1)
Socket.__xor__  = lambda slf, s : bitwise_xor(slf, s)
Socket.__rxor__ = Socket.__xor__

__all__ = ['add', 'sub', 'mul', 'div', 'greater_equal', 'greater',
           'equal', 'not_equal', 'less_equal', 'less', 'bitwise_and',
           'bitwise_or', 'bitwise_xor']