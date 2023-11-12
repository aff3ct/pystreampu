"""
Provides elementwise unary operators (uop).

Elementwise unary operations are such that `z[i] = uop(x[i])`.
"""

from enum import Enum, auto

import aff3ct._ext
from aff3ct._ext import dtype, int8
from aff3ct._ext.core import Module, Socket


class UType(Enum):
    """Unary operator type enum."""

    ABS = auto()
    NEG = auto()
    NOT = auto()
    CAST = auto()

    def __str__(self) -> str:
        """Return string representation of enum items.

        Returns:
            str : Item as string.
        """
        return self.name.lower()


def _uop_factory(n_elmts: int,
                 uop_type: UType,
                 input_dtype: dtype = int8,
                 output_dtype: dtype = int8) -> Module:
    """Return an AFF3CT unary operator module.

    Args:
        n_elmts (int): number of elements
        uop_type (UType): Name of the unary operator to instantiate
        input_dtype (dtype): Input data type
        output_dtype (dtype): Input data type

    Returns:
        Module: AFF3CT module unary operator

    Raises:
        TypeError: if input_type or output_type are not dtypes
    """
    if not isinstance(input_dtype, dtype):
        msg = f"type '{type(input_dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)

    if not isinstance(output_dtype, dtype):
        msg = f"type '{type(input_dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)

    name = f'Unaryop_{str(uop_type)}_{input_dtype.name}_{output_dtype.name}'
    uop_class = getattr(aff3ct._ext.uop, name)
    return uop_class(n_elmts)


def uop(uop_type: UType,
        sckt: Socket,
        output_dtype: dtype = None) -> Socket:
    """Apply unary operator on socket data.

    Args:
        uop_type (UType): Type of unary operator
        sckt (Socket): unary operator input
        output_dtype(dtype): output data type

    Returns:
        Socket: Modified socket.
    """
    input_dtype = sckt.dtype
    if not output_dtype:
        output_dtype = input_dtype
    n_frames = sckt.task.module.n_frames
    n_elmts_frame = sckt.n_elmts // n_frames
    mdl = _uop_factory(n_elmts_frame, str(uop_type), input_dtype, output_dtype)
    mdl.n_frames = n_frames
    return mdl.perform(sckt)


def abs(sckt: Socket,
         output_dtype: dtype = None) -> Socket:
    """Return abs(sckt).

    Args:
        sckt (Socket): input data.
        output_dtype (dtype): input data type.

    Returns:
        Socket: abs(s)
    """
    return uop(UType.ABS, sckt, output_dtype)


def neg(sckt: Socket,
        output_dtype: dtype = None) -> Socket:
    """Compute -sckt.

    Args:
        sckt (Socket): input data.
        output_dtype (dtype): input data type.

    Returns:
        Socket: -sckt
    """
    return uop(UType.NEG, sckt, output_dtype)


def bitwise_not(sckt: Socket,
                output_dtype: dtype = None) -> Socket:
    """Compute ~sckt bitwise.

    Args:
        sckt (Socket): input data.
        output_dtype (dtype): input data type.

    Returns:
        Socket: !sckt
    """
    return uop(UType.NOT, sckt, output_dtype)


def cast(sckt: Socket,
         output_dtype: dtype = None) -> Socket:
    """Cast sckt to dtype.

    Args:
        sckt (Socket): input data.
        output_dtype (dtype): input data type.

    Returns:
        Socket: dtype(sckt)
    """
    if not dtype:
        return sckt

    return uop(UType.CAST, sckt, output_dtype)


__all__ = ['UType', 'uop', 'abs', 'neg', 'bitwise_not', 'cast']
