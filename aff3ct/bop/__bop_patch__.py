import numpy as np
from .. import builtins
from .. import array
from .Binaryop import Binaryop

def bop_generic_factory(name:str, s0:builtins.core.Socket, s1:any, fwd = False): #, invert:bool = False
    n_frames = s0.task.module.n_frames
    TI = s0.dtype

    if type(s1) is not builtins.core.Socket:
        s1 = builtins.core.Socket.from_array(s1, dtype = s0.dtype, n_frames = n_frames)

    TO = TI
    if name in ["eq", "ge", "gt", "le", "lt", "ne"]:
        TO = builtins.int32

    n_in1 = s0.n_elmts//n_frames
    n_in2 = s1.n_elmts//n_frames

    the_bop = Binaryop(n_in1, n_in2, name, TI, TO)
    the_bop.n_frames = n_frames

    if fwd:
        the_bop.fwd_perform(s0,s1)
        return s0
    else:
        s = the_bop.perform(s0,s1)
        return s

Socket = builtins.core.Socket

def add (s0, s1): return bop_generic_factory("add",s0,s1)
Socket.__add__  = lambda slf, s : add(slf, s)
Socket.__radd__ = Socket.__add__

def iadd (s0, s1): return bop_generic_factory("add",s0,s1,fwd=True)
Socket.__iadd__  = lambda slf, s : iadd(slf, s)

def sub  (s0, s1): return bop_generic_factory("sub",s0,s1)
Socket.__sub__  = lambda slf, s : sub(slf, s)
def rsub (s0, s1): return bop_generic_factory("sub",s1,s0)
Socket.__rsub__ = lambda slf, s : rsub(slf, s)

def mul (s0, s1): return bop_generic_factory("mul",s0,s1)
Socket.__mul__  = lambda slf, s : mul(slf, s)
Socket.__rmul__ = Socket.__mul__

def div (s0, s1): return bop_generic_factory("div",s0,s1)
Socket.__truediv__  = lambda slf, s : div(slf, s)
def rdiv (s0, s1): return bop_generic_factory("div",s1,s0)
Socket.__rtruediv__ = lambda slf, s : rdiv(slf, s)

def greater_equal (s0, s1): return bop_generic_factory("ge",s0,s1)
Socket.__ge__  = lambda slf, s : greater_equal(slf, s)
def rgreater_equal (s0, s1): return bop_generic_factory("ge",s1,s0)
Socket.__rge__ = lambda slf, s : rgreater_equal(slf, s)

def greater (s0, s1): return bop_generic_factory("gt",s0,s1)
Socket.__gt__  = lambda slf, s : greater(slf, s)
def rgreater (s0, s1): return bop_generic_factory("gt",s1,s0)
Socket.__rgt__  = lambda slf, s : rgreater(slf, s)

def equal (s0, s1): return bop_generic_factory("eq",s0,s1)
Socket.__eq__  = lambda slf, s : equal(slf, s)
Socket.__req__ = Socket.__eq__

def not_equal (s0, s1): return bop_generic_factory("neq",s0,s1)
Socket.__neq__  = lambda slf, s : not_equal(slf, s)
Socket.__rneq__ = Socket.__neq__

def less_equal (s0, s1): return bop_generic_factory("le",s0,s1)
Socket.__le__  = lambda slf, s : less_equal(slf, s)
def rless_equal (s0, s1): return bop_generic_factory("le",s1,s0)
Socket.__rle__ = lambda slf, s : rless_equal(slf, s)

def less (s0, s1): return bop_generic_factory("lt",s0,s1)
Socket.__lt__  = lambda slf, s : less(slf, s)
def rless (s0, s1): return bop_generic_factory("lt",s1,s0)
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