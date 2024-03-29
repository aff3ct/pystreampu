"""Add some magic functions to the Socket class."""
from __future__ import annotations

from typing import Union

import numpy as np

from aff3ct._ext.sli import Slicer
from aff3ct._ext.core import Socket

from . import _bop, _uop, _red
from ._array import array
from ._dtype import dtype
from ._typing import SocketLike


def _str(self: Socket) -> str:
    """Return the socket as a str.

    Args:
        self (Socket): A socket

    Returns:
        out (str): str representing the socket's data
    """
    return str(self.numpy)


Socket.__str__ = _str


def _len(self: Socket) -> int:
    """Return the size of one frame.

    Args:
        self (Socket): A socket

    Returns:
        out (int): size of one frame
    """
    return self.n_elmts // self.task.module.n_frames


Socket.__len__ = _len


def _repr(self: Socket) -> str:
    """Return a socket representation.

    Args:
        self (Socket): A socket

    Returns:
        out (str): a str representing the socket
    """
    data_ = str(self.numpy).splitlines()

    if len(data_) > 1:
        data_[0] += '\n'
        data_[-1] = '       ' + data_[-1]
        for i in range(1, len(data_)-1):
            data_[i] = '       ' + data_[i] + '\n'

    data_str = ''.join(data_)
    out = f'socket({data_str}, dtype={self.dtype.name}, name={self.name}, '
    out += f'task={self.task.module.name}.{self.task.name})'
    return out


Socket.__repr__ = _repr


def _bind_(self: Socket, s_out: SocketLike, priority: int = 1, raw_data=False) -> None:
    """Binds self to s_out.

    If s_out is not a `Socket`, s_out is converted to a `Socket` first.

    Args:
        self (Socket): A socket
        s_out (SocketLike): Socket to bind
        priority (int): Priority of the bind.
        raw_data (bool): if True converts data to a Socket
    """
    if raw_data:
        self._bind(np.array(s_out, copy=False))
        return

    if not isinstance(s_out, Socket):
        if hasattr(s_out, "dtype"):
            s_out = array(s_out, dtype=dtype.of(str(s_out.dtype)))
        else:
            s_out = array(s_out)
    else:
        while hasattr(s_out, '_mrv'):
            s_out = s_out._mrv

    self._tag = s_out

    if self.direction == Socket.directions.FWD:
        # If slf is a forward socket,
        # then it will be the most recent value of s_out
        s_out._mrv = self

    self._bind(s_out, priority)


Socket.bind = _bind_


def _setitem(self: Socket, key: Union[int, slice], data: SocketLike) -> Socket:
    """Write data at place key inside a socket.

    Args:
        self (Socket): input data
        key (int|slice): place to write the new data
        data (SocketLike): new data
    """
    slc = None
    if isinstance(key, slice):
        len_ = self.n_elmts // self.task.module.n_frames
        start, stop, step = key.indices(len_)
        slc = Slicer(self, np.arange(start, stop, step))

    if isinstance(key, int):
        slc = Slicer(self, key)

    slc.n_frames = self.task.module.n_frames
    if hasattr(data, '__len__') and len(data) > 1:
        slc.write(self, data)
    else:
        slc.write_one(self, data)

    if not hasattr(self, '_slicers'):
        self._slicers = []
    self._slicers.append(slc)


Socket.__setitem__ = _setitem


def _getitem(self: Socket, key: Union[slice, int]) -> Socket:
    """Read data at place key inside a socket.

    Args:
        self (Socket): input data
        key (int|slice): place to write the new data

    Returns:
        out (Socket): self[key]
    """
    slc = None
    if isinstance(key, slice):
        len_ = self.n_elmts // self.task.module.n_frames
        start, stop, step = key.indices(len_)
        slc = Slicer(self, np.arange(start, stop, step))

    if isinstance(key, int):
        slc = Slicer(self, key)

    slc.n_frames = self.task.module.n_frames

    if not hasattr(self, '_slicers'):
        self._slicers = []
    self._slicers.append(slc)

    return slc.read(self)


Socket.__getitem__ = _getitem


def _add(self: Socket, value: SocketLike) -> Socket:
    """Compute self + value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  self + value
    """
    return _bop.bop(_bop.BType.ADD, self, value)


Socket.__add__ = _add


def _iadd(self: Socket, value: SocketLike) -> Socket:
    """Compute self += value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  updated self (in-place operation)
    """
    return _bop.bop(_bop.BType.ADD, self, value, fwd=True)


Socket.__iadd__ = _iadd


def _radd(self: Socket, value: SocketLike) -> Socket:
    """Compute value + self.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  value + self
    """
    return _bop.bop(_bop.BType.ADD, self, value, rev=True)


Socket.__radd__ = _radd


def _sub(self: Socket, value: SocketLike) -> Socket:
    """Compute self - value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  self - value
    """
    return _bop.bop(_bop.BType.SUB, self, value)


Socket.__sub__ = _sub


def _isub(self: Socket, value: SocketLike) -> Socket:
    """Compute self -= value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  updated self (in-place operation)
    """
    return _bop.bop(_bop.BType.SUB, self, value, fwd=True)


Socket.__isub__ = _isub


def _rsub(self: Socket, value: SocketLike) -> Socket:
    """Compute value - self.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  value - self
    """
    return _bop.bop(_bop.BType.SUB, self, value, rev=True)


Socket.__rsub__ = _rsub


def _mul(self: Socket, value: SocketLike) -> Socket:
    """Compute self * value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  self * value
    """
    return _bop.bop(_bop.BType.MUL, self, value)


Socket.__mul__ = _mul


def _imul(self: Socket, value: SocketLike) -> Socket:
    """Compute self = self * value with in-place operation.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  updated self (in-place operation)
    """
    return _bop.bop(_bop.BType.MUL, self, value, fwd=True)


Socket.__imul__ = _imul


def _rmul(self: Socket, value: SocketLike) -> Socket:
    """Compute value * self.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  value * self
    """
    return _bop.bop(_bop.BType.MUL, self, value, rev=True)


Socket.__rmul__ = _rmul


def _truediv(self: Socket, value: SocketLike) -> Socket:
    """Compute self / value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  self / value
    """
    return _bop.bop(_bop.BType.DIV, self, value)


Socket.__truediv__ = _truediv


def _itruediv(self: Socket, value: SocketLike) -> Socket:
    """Compute self /= value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  updated self (in-place operation)
    """
    return _bop.bop(_bop.BType.DIV, self, value, fwd=True)


Socket.__itruediv__ = _itruediv


def _rtruediv(self: Socket, value: SocketLike) -> Socket:
    """Compute value / self.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  value / self
    """
    return _bop.bop(_bop.BType.DIV, self, value, rev=True)


Socket.__rtruediv__ = _rtruediv


def _ge(self: Socket, value: SocketLike) -> Socket:
    """Compute self >= value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  self >= value
    """
    return _bop.bop(_bop.BType.GE, self, value)


Socket.__ge__ = _ge


def _rge(self: Socket, value: SocketLike) -> Socket:
    """Compute value >= self.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  value >= self
    """
    return _bop.bop(_bop.BType.GE, self, value, rev=True)


Socket.__rge__ = _rge


def _gt(self: Socket, value: SocketLike) -> Socket:
    """Compute self > value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  self > value
    """
    return _bop.bop(_bop.BType.GT, self, value)


Socket.__gt__ = _gt


def _rgt(self: Socket, value: SocketLike) -> Socket:
    """Compute value > self.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  value > self
    """
    return _bop.bop(_bop.BType.GT, self, value, rev=True)


Socket.__rgt__ = _rgt


def _eq(self: Socket, value: SocketLike) -> Socket:
    """Compute value == self.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  value == self
    """
    return _bop.bop(_bop.BType.EQ, self, value)


Socket.__eq__ = _eq


def _req(self: Socket, value: SocketLike) -> Socket:
    """Compute self == value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  self == value
    """
    return _bop.bop(_bop.BType.EQ, self, value, rev=True)


Socket.__req__ = _req


def _ne(self: Socket, value: SocketLike) -> Socket:
    """Compute self != value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  self != value
    """
    return _bop.bop(_bop.BType.NE, self, value)


Socket.__ne__ = _ne


def _rneq(self: Socket, value: SocketLike) -> Socket:
    """Compute value != self.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  value != self
    """
    return _bop.bop(_bop.BType.NEQ, self, value, rev=True)


Socket.__rneq__ = _rneq


def _le(self: Socket, value: SocketLike) -> Socket:
    """Compute self <= value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  self <= value
    """
    return _bop.bop(_bop.BType.LE, self, value)


Socket.__le__ = _le


def _rle(self: Socket, value: SocketLike) -> Socket:
    """Compute value <= self.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  value <= self
    """
    return _bop.bop(_bop.BType.LE, self, value, rev=True)


Socket.__rle__ = _rle


def _lt(self: Socket, value: SocketLike) -> Socket:
    """Compute self < value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  self < value
    """
    return _bop.bop(_bop.BType.LT, self, value)


Socket.__lt__ = _lt


def _rlt(self: Socket, value: SocketLike) -> Socket:
    """Compute value < self.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  value < self
    """
    return _bop.bop(_bop.BType.LT, self, value, rev=True)


Socket.__rlt__ = _rlt


def _sand(self: Socket, value: SocketLike) -> Socket:
    """Compute self & value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  self & value
    """
    return _bop.bop(_bop.BType.AND, self, value)


Socket.__and__ = _sand


def _iand(self: Socket, value: SocketLike) -> Socket:
    """Compute self &= value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  updated self (in-place operation)
    """
    return _bop.bop(_bop.BType.AND, self, value, fwd=True)


Socket.__iand__ = _iand


def _rand(self: Socket, value: SocketLike) -> Socket:
    """Compute value & self.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  value & value
    """
    return _bop.bop(_bop.BType.AND, self, value, rev=True)


Socket.__rand__ = _rand


def _or(self: Socket, value: SocketLike) -> Socket:
    """Compute self | value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  self | value
    """
    return _bop.bop(_bop.BType.OR, self, value)


Socket.__or__ = _or


def _ior(self: Socket, value: SocketLike) -> Socket:
    """Compute self = self | value with in-place operation.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  updated self (in-place operation)
    """
    return _bop.bop(_bop.BType.OR, self, value, fwd=True)


Socket.__ior__ = _ior


def _ror(self: Socket, value: SocketLike) -> Socket:
    """Compute value | self.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  value | self
    """
    return _bop.bop(_bop.BType.OR, self, value, rev=True)


Socket.__ror__ = _ror


def _xor(self: Socket, value: SocketLike) -> Socket:
    """Compute self ^ value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  self ^ value
    """
    return _bop.bop(_bop.BType.XOR, self, value)


Socket.__xor__ = _xor


def _ixor(self: Socket, value: SocketLike) -> Socket:
    """Compute self ^= value.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  updated self (in-place operation)
    """
    return _bop.bop(_bop.BType.XOR, self, value, fwd=True)


Socket.__ixor__ = _ixor


def _rxor(self: Socket, value: SocketLike) -> Socket:
    """Compute value ^ self.

    Args:
        self (Socket): input data
        value (SocketLike): a value

    Returns:
        out (Socket):  value ^ self
    """
    return _bop.bop(_bop.BType.XOR, self, value, rev=True)


Socket.__rxor__ = _rxor


def _abs(self: Socket) -> Socket:
    """Compute abs(self).

    Args:
        self (Socket): input data

    Returns:
        out (Socket):  abs(self)
    """
    return _uop.abs(self)


Socket.__abs__ = _abs


def _neg(self: Socket) -> Socket:
    """Compute -self.

    Args:
        self (Socket): input data

    Returns:
        out (Socket):  -self
    """
    return _uop.neg(self)


Socket.__neg__ = _neg


def _invert(self: Socket) -> Socket:
    """Compute ~self.

    Args:
        self (Socket): input data

    Returns:
        out (Socket):  ~self
    """
    return _uop.bitwise_not(self)


Socket.__invert__ = _invert


def _astype(self: Socket, output_dtype: dtype) -> Socket:
    """Cast socket to dtype.

    Args:
        self (Socket): input data
        output_dtype (dtype): output data type

    Returns:
        out (Socket):  output_dtype(self)
    """
    return _uop.cast(self, output_dtype)


Socket.astype = _astype


__all__ = ['Socket']
