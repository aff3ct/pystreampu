# encoding: utf-8
r"Add some magic functions to :aff3ct._ext.core.Socket:"

import numpy as np
from typing import Union
import aff3ct
from aff3ct._ext      import Slicer
from ._array          import array
from .                import _bop
from .                import _uop
from ._dtype          import int32

Socket = aff3ct._ext.core.Socket


def _numpy(self:Socket)->np.array:
    return np.array(self)


Socket.numpy = _numpy


def _str(self:Socket)->str:
    """Get a str representing a socket."""
    return np.array(self).__str__()


Socket.__str__ = _str


def _len(self:Socket)->int:
    """Get the socket length."""
    return self.n_elmts//self.task.module.n_frames


Socket.__len__ = _len


def _repr(self:Socket)->str:
    """Prints a socket."""
    data_str = self.__str__()
    str = f"socket({data_str}, dtype={self.dtype.name}, name={self.name}, task={self.task.module.name}.{self.task.name})"
    return str


Socket.__repr__ = _repr


def _bind(self:Socket, s_out, priority:int = 1) -> None:
    """
    Binds self to s_out. If s_out is not a `Socket`, s_out is converted to a `Socket` first.

    Parameters
    ----------
    s_out : SocketLike
            Socket to bind

    priority : :int:
                Priority of the bind.
    """
    # The __tag__ attribute of module will store the modules which are binded
    # to the tasks of mdl
    mdl = self.task.module
    if not hasattr(mdl, "__tag__"):
        mdl.__tag__ = dict.fromkeys([tsk.name for tsk in mdl.tasks], {})

    if type(s_out) is not Socket:
        s_out = array(s_out)
    else:
        while hasattr(s_out, "__mrv__"):
            s_out = s_out.__mrv__

    mdl.__tag__[self.task.name][self.name] = s_out

    if self.direction == Socket.directions.FWD:
        # If slf is a forward socket, then it will be the most recent value of s_out
        s_out.__mrv__ = self

    self.__bind__(s_out, priority)


Socket.bind = _bind


def _setitem(self, key, data):
    slc = None
    if type(key) is slice:
        start, stop, step = key.indices(self.n_elmts // self.task.module.n_frames)
        slc = Slicer(self, np.arange(start, stop, step))
    elif type(key) is int:
        slc = Slicer(self, key)

    slc.n_frames = self.task.module.n_frames
    if hasattr(data,"__len__") and len(data) > 1:
        slc.write(self, data)
    else:
        slc.write_one(self, data)

    #TODO : fix this
    if not hasattr(self, "__slicers__"):
        self.__slicers__ = []
    self.__slicers__.append(slc)


Socket.__setitem__ = _setitem


def _getitem(self:Socket, key:Union[slice,int]):
    slc = None
    if type(key) is slice:
        start, stop, step = key.indices(self.n_elmts // self.task.module.n_frames)
        slc = Slicer(self, np.arange(start, stop, step))
    elif type(key) is int:
        slc = Slicer(self, key)

    slc.n_frames = self.task.module.n_frames

    #TODO : fix this
    if not hasattr(self, "__slicers__"):
        self.__slicers__ = []
    self.__slicers__.append(slc)

    return slc.read(self)


Socket.__getitem__ = _getitem


def _add(self, value):
    """:return: self + s."""
    return _bop.bop(_bop.BType.ADD, self, value)


Socket.__add__ = _add


def _iadd(self, value):
    """:return: self += value."""
    return _bop.bop(_bop.BType.ADD, self, value, fwd=True)


Socket.__iadd__ = _iadd


def _radd(self, value):
    """:return: value + self."""
    return _bop.bop(_bop.BType.ADD, self, value, rev=True)


Socket.__radd__ = _radd


def _sub(self, value):
    """:return: self - s."""
    return _bop.bop(_bop.BType.SUB, self, value)


Socket.__sub__ = _sub


def _isub(self, value):
    """:return: self -= value."""
    return _bop.bop(_bop.BType.SUB, self, value, fwd=True)


Socket.__isub__ = _isub


def _rsub(self, value):
    """:return: value - self."""
    return _bop.bop(_bop.BType.SUB, self, value, rev=True)


Socket.__rsub__ = _rsub


def _mul(self, value):
    """:return: self * s."""
    return _bop.bop(_bop.BType.MUL, self, value)


Socket.__mul__ = _mul


def _imul(self, value):
    """:return: self *= value."""
    return _bop.bop(_bop.BType.MUL, self, value, fwd=True)


Socket.__imul__ = _imul


def _rmul(self, value):
    """:return: value * self."""
    return _bop.bop(_bop.BType.MUL, self, value, rev=True)


Socket.__rmul__ = _rmul


def _truediv(self, value):
    """:return: self / s."""
    return _bop.bop(_bop.BType.DIV, self, value)


Socket.__truediv__ = _truediv


def _itruediv(self, value):
    """:return: self /= value."""
    return _bop.bop(_bop.BType.DIV, self, value, fwd=True)


Socket.__itruediv__ = _itruediv


def _rtruediv(self, value):
    """:return: value / self."""
    return _bop.bop(_bop.BType.DIV, self, value, rev=True)


Socket.__rtruediv__ = _rtruediv


def _ge(self, value):
    """:return: self >= s."""
    return _bop.bop(_bop.BType.GE, self, value)


Socket.__ge__ = _ge


def _rge(self, value):
    """:return: value >= self."""
    return _bop.bop(_bop.BType.GE, self, value, rev=True)


Socket.__rge__ = _rge


def _gt(self, value):
    """:return: self > s."""
    return _bop.bop(_bop.BType.GT, self, value)


Socket.__gt__ = _gt


def _rgt(self, value):
    """:return: value > self."""
    return _bop.bop(_bop.BType.GT, self, value, rev=True)


Socket.__rgt__ = _rgt


def _eq(self, value):
    """:return: self == s."""
    return _bop.bop(_bop.BType.EQ, self, value)


Socket.__eq__ = _eq


def _req(self, value):
    """:return: value == self."""
    return _bop.bop(_bop.BType.EQ, self, value, rev=True)


Socket.__req__ = _req


def _neq(self, value):
    """:return: self != s."""
    return _bop.bop(_bop.BType.NEQ, self, value)


Socket.__neq__ = _neq


def _rneq(self, value):
    """:return: value != self."""
    return _bop.bop(_bop.BType.NEQ, self, value, rev=True)


Socket.__rneq__ = _rneq


def _le(self, value):
    """:return: self <= s."""
    return _bop.bop(_bop.BType.LE, self, value)



Socket.__le__ = _le


def _rle(self, value):
    """:return: value <= self."""
    return _bop.bop(_bop.BType.LE, self, value, rev=True)


Socket.__rle__ = _rle


def _lt(self, value):
    """:return: self < s."""
    return _bop.bop(_bop.BType.LT, self, value)


Socket.__lt__ = _lt


def _rlt(self, value):
    """:return: value < self."""
    return _bop.bop(_bop.BType.LT, self, value, rev=True)


Socket.__rlt__ = _rlt


def _and(self, value):
    """:return: self & s."""
    return _bop.bop(_bop.BType.AND, self, value)


Socket.__and__ = _and


def _iand(self, value):
    """:return: self &= value."""
    return _bop.bop(_bop.BType.AND, self, value, fwd=True)


Socket.__iand__ = _iand


def _rand(self, value):
    """:return: value & self."""
    return _bop.bop(_bop.BType.AND, self, value, rev=True)


Socket.__rand__ = _rand


def _or(self, value):
    """:return: self | s."""
    return _bop.bop(_bop.BType.OR, self, value)


Socket.__or__ = _or


def _ior(self, value):
    """:return: self |= value."""
    return _bop.bop(_bop.BType.OR, self, value, fwd=True)


Socket.__ior__ = _ior


def _ror(self, value):
    """:return: value | self."""
    return _bop.bop(_bop.BType.OR, self, value, rev=True)


Socket.__ror__ = _ror


def _xor(self, value):
    """:return: self ^ s."""
    return _bop.bop(_bop.BType.XOR, self, value)


Socket.__xor__ = _xor


def _ixor(self, value):
    """:return: self ^= value."""
    return _bop.bop(_bop.BType.XOR, self, value, fwd=True)


Socket.__ixor__ = _ixor


def _rxor(self, value):
    """:return: value ^ self."""
    return _bop.bop(_bop.BType.XOR, self, value, rev=True)


Socket.__rxor__ = _rxor


def _abs(self):
    """:return: |self|."""
    return _uop.abs(self)


Socket.__abs__ = _abs


def _neg(self):
    """:return: -self."""
    return _uop.neg(self)


Socket.__neg__ = _neg


def _invert(self):
    """:return: ~self."""
    return _uop.bitwise_not(self)


Socket.__invert__ = _invert


def _astype(self, dtype):
    """:return: a cast of self as dtype."""
    return _uop.cast(self, dtype)


Socket.astype = _astype
__all__ = ['Socket']
