"""
Provides elementwise binary operators (bop).

Elementwise binary operations are such that `z[i] = bop(s_0[i], s_1[i])`.
"""

from enum import Enum, auto

import aff3ct._ext
from aff3ct import array
from aff3ct._ext import dtype, int8, int32
from aff3ct._ext.core import Module, Socket
from aff3ct._typing import SocketLike

import numpy as np

class BType(Enum):
    """Binary operator enum."""

    ADD = auto()
    SUB = auto()
    MUL = auto()
    DIV = auto()
    GE = auto()
    GT = auto()
    LE = auto()
    LT = auto()
    EQ = auto()
    NE = auto()
    AND = auto()
    OR = auto()
    XOR = auto()
    MIN = auto()
    MAX = auto()

    def __str__(self) -> str:
        """Return string representation of enum items.

        Returns:
            str : Item as string.
        """
        return self.name.lower()


def _bop_factory(
    n_in0: int,
    n_in1: int,
    bop_type: BType,
    input_type: dtype = int8,
    output_type: dtype = int8,
) -> Module:
    """Build a binary operator module.

    Args:
        n_in0 (int): Number of elements of input socket in0
        n_in1 (int): Number of elements of input socket in1
        bop_type (BType): Type of the binary operator
        input_type (dtype): Input data type
        output_type (dtype): Output data type

    Returns:
        out (Module): AFF3CT module binary operator

    Raises:
        TypeError: if input_type or output_type are not dtypes
        AttributeError: if no binary operator can be built
    """
    if not issubclass(type(input_type), dtype):
        ex_msg = f"type '{type(input_type)}' does not name an AFF3CT dtype."
        raise TypeError(ex_msg)

    if not issubclass(type(output_type), dtype):
        ex_msg = f"type '{type(output_type)}' does not name an AFF3CT dtype."
        raise TypeError(ex_msg)

    name = f'Binaryop_{str(bop_type)}_{input_type.name}_{output_type.name}'

    try:
        return getattr(aff3ct._ext.bop, name)(n_in0, n_in1)
    except AttributeError as exc:
        ex_msg = f"binary operator '{name}' does not exist."
        raise AttributeError(ex_msg) from exc


def bop(bop_type: BType,
        s_0: Socket,
        s_1: SocketLike,
        fwd: bool = False,
        rev: bool = False,
        output_dtype: dtype = None) -> Socket:
    """
    Binary operator factory from Sockets.

    Args:
        bop_type (BType): Type of binary operator
        s_0 (Socket): First input of the binary operator (must be a Socket).
        s_1 (SocketLike): Second input of the binary operator.
        fwd (bool): If true, performs operations in place.
        rev (bool): If true, exchange s_0 and s_1 (for right-bops).
        output_dtype(dtype): output data type

    Returns:
        out (Socket): Binary operation elementwise result.
    """
    name = str(bop_type)
    n_frames = s_0.task.module.n_frames
    input_dtype = s_0.dtype

    s_1 = array(s_1, dtype=s_0.dtype)

    if fwd:
        s = s_1
        s_1 = s_0
        s_0 = s

    if not output_dtype:
        output_dtype = input_dtype

    comparisons = ['eq', 'ge', 'gt', 'le', 'lt', 'ne']
    if name in comparisons and not output_dtype:
        output_dtype = int32

    n_in0 = s_0.n_elmts // n_frames
    n_in1 = s_1.n_elmts // n_frames
    the_bop = _bop_factory(n_in0, n_in1, bop_type, input_dtype, output_dtype)
    the_bop.n_frames = n_frames

    if fwd:
        the_bop.performf(s_0, s_1)
        return s_1

    if rev:
        return the_bop.perform(s_1, s_0)

    return the_bop.perform(s_0, s_1)


def add(s_0: Socket,
        s_1: Socket,
        output_dtype: dtype = None) -> Socket:
    """
    Add two sockets componentwise.

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype (dtype): dtype of the output socket

    Returns:
        out (Socket): out[i] = s_0[i] + s_1[i]
    """
    return bop(BType.ADD, s_0, s_1, output_dtype=output_dtype)


def sub(s_0: Socket,
        s_1: Socket,
        output_dtype: dtype = None) -> Socket:
    """
    Substract two sockets componentwise.

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype (dtype): dtype of the output socket

    Returns:
        out (Socket): z[i] = s_0[i] - s_1[i]
    """
    return bop(BType.SUB, s_0, s_1, output_dtype=output_dtype)


def mul(s_0: Socket,
        s_1: Socket,
        output_dtype: dtype = None) -> Socket:
    """
    Multiply two sockets componentwise.

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype(dtype): dtype of the output socket

    Returns:
        out (Socket): z[i] = s_0[i] * s_1[i]
    """
    return bop(BType.MUL, s_0, s_1, output_dtype=output_dtype)


def div(s_0: Socket,
        s_1: Socket,
        output_dtype: dtype = None) -> Socket:
    """
    Divide two sockets componentwise.

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype(dtype): dtype of the output socket

    Returns:
        out (Socket): z[i] = s_0[i] / s_1[i]
    """
    return bop(BType.DIV, s_0, s_1, output_dtype=output_dtype)


def greater_equal(s_0: Socket,
                  s_1: Socket,
                  output_dtype: dtype = None) -> Socket:
    """
    Compare two sockets componentwise (>=).

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype(dtype): dtype of the output socket

    Returns:
        out (Socket): z[i] = (s_0[i] >= s_1[i])
    """
    return bop(BType.GE, s_0, s_1, output_dtype=output_dtype)


def greater(s_0: Socket,
            s_1: Socket,
            output_dtype: dtype = None) -> Socket:
    """
    Compare two sockets componentwise (>).

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype(dtype): dtype of the output socket

    Returns:
        out (Socket): z[i] = (s_0[i] > s_1[i])
    """
    return bop(BType.GT, s_0, s_1, output_dtype=output_dtype)


def equal(s_0: Socket,
          s_1: Socket,
          output_dtype: dtype = None) -> Socket:
    """
    Compare two sockets componentwise (==).

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype(dtype): dtype of the output socket

    Returns:
        out (Socket): z[i] = (s_0[i] == s_1[i])
    """
    return bop(BType.EQ, s_0, s_1, output_dtype=output_dtype)


def not_equal(s_0: Socket,
              s_1: Socket,
              output_dtype: dtype = None) -> Socket:
    """
    Compare two sockets componentwise (!=).

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype(dtype): dtype of the output socket

    Returns:
        out (Socket): z[i] = (s_0[i] != s_1[i])
    """
    return bop(BType.NEQ, s_0, s_1, output_dtype=output_dtype)


def less_equal(s_0: Socket,
               s_1: Socket,
               output_dtype: dtype = None) -> Socket:
    """
    Compare two sockets componentwise (<=).

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype(dtype): dtype of the output socket

    Returns:
        out (Socket): z[i] = (s_0[i] <= s_1[i])
    """
    return bop(BType.LE, s_0, s_1, output_dtype=output_dtype)


def less(s_0: Socket,
         s_1: Socket,
         output_dtype: dtype = None) -> Socket:
    """
    Compare two sockets componentwise (<).

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype(dtype): dtype of the output socket

    Returns:
        out (Socket): z[i] = (s_0[i] < s_1[i])
    """
    return bop(BType.LT, s_0, s_1, output_dtype=output_dtype)


def bitwise_and(s_0: Socket,
                s_1: Socket,
                output_dtype: dtype = None) -> Socket:
    """
    Compute bitwise AND between two sockets componentwise.

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype(dtype): dtype of the output socket

    Returns:
        out(Socket): z[i] = (s_0[i] & s_1[i])
    """
    return bop(BType.AND, s_0, s_1, output_dtype=output_dtype)


def bitwise_or(s_0: Socket,
               s_1: Socket,
               output_dtype: dtype = None) -> Socket:
    """
    Compute bitwise OR between two sockets componentwise.

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype(dtype): dtype of the output socket

    Returns:
        out(Socket): z[i] = (s_0[i] | s_1[i])
    """
    return bop(BType.OR, s_0, s_1, output_dtype=output_dtype)


def bitwise_xor(s_0: Socket,
                s_1: Socket,
                output_dtype: dtype = None) -> Socket:
    """
    Compute bitwise XOR between two sockets componentwise.

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype(dtype): dtype of the output socket

    Returns:
        out(Socket): out[i] = (s_0[i] ^ s_1[i])
    """
    return bop(BType.XOR, s_0, s_1, output_dtype=output_dtype)

def min(s_0: Socket,
        s_1: Socket,
        output_dtype: dtype = None) -> Socket:
    """
    Compute componentwise min.

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype(dtype): dtype of the output socket

    Returns:
        out(Socket): out[i] = min(s_0[i], s_1[i])
    """
    return bop(BType.MIN, s_0, s_1, output_dtype=output_dtype)

def max(s_0: Socket,
        s_1: Socket,
        output_dtype: dtype = None) -> Socket:
    """
    Compute componentwise max.

    Args:
        s_0 (Socket): sockets to process
        s_1 (Socket): sockets to process
        output_dtype(dtype): dtype of the output socket

    Returns:
        out(Socket): out[i] = max(s_0[i], s_1[i])
    """
    return bop(BType.MAX, s_0, s_1, output_dtype=output_dtype)


__all__ = ['BType',
           'bop',
           'add',
           'sub',
           'mul',
           'div',
           'greater_equal',
           'greater',
           'equal',
           'not_equal',
           'less_equal',
           'less',
           'bitwise_and',
           'bitwise_or',
           'bitwise_xor',
           'min',
           'max']
