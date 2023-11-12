from enum import Enum, auto

import aff3ct._ext
from aff3ct._ext import dtype, int8, int32
from aff3ct._ext.core import Module, Socket
from aff3ct._typing import SocketLike

class RType(Enum):
    """Reducer operator type enum."""

    ADD = auto()
    MUL = auto()
    MIN = auto()
    MAX = auto()
    OR = auto()
    AND = auto()

    def __str__(self) -> str:
        """Return string representation of enum items.

        Returns:
            str : Item as string.
        """
        return self.name.lower()


def _red_factory(
    n_in: int,
    red_type: RType,
    input_type: dtype = int8,
    output_type: dtype = int8,
) -> Module:
    """Build a Reducer module.

    Args:
        n_in (int): Number of elements of input socket
        red_type (RType): Type of the reduction
        input_type (dtype): Input data type
        output_type (dtype): Output data type

    Returns:
        Module: built reducer

    Raises:
        TypeError: if input_type or output_type are not dtypes
        AttributeError: if no Reducer can be built
    """
    if not issubclass(type(input_type), dtype):
        ex_msg = f"type '{type(input_type)}' does not name an AFF3CT dtype."
        raise TypeError(ex_msg)

    if not issubclass(type(output_type), dtype):
        ex_msg = f"type '{type(output_type)}' does not name an AFF3CT dtype."
        raise TypeError(ex_msg)

    try:
        name = f'Reducer_{str(red_type)}_{input_type.name}_{output_type.name}'
        return getattr(aff3ct._ext.red, name)(n_in)
    except AttributeError as exc:
        ex_msg = f"binary operator '{name}' does not exist."
        raise AttributeError(ex_msg) from exc


def red(red_type: RType,
        sckt: Socket,
        output_dtype: dtype = None) -> Socket:
    """
    Reduce a socket content.

    Args:
        red_type (RType): Type of reduction
        sckt (Socket): Socket to reduce.
        output_dtype(dtype): output data type

    Returns:
        Socket: Reduced socket.
    """
    red_name = str(red_type)
    n_frames = sckt.task.module.n_frames
    input_dtype = sckt.dtype

    if not output_dtype:
        output_dtype = input_dtype

    n_in = sckt.n_elmts // n_frames

    the_red = _red_factory(n_in, red_name, input_dtype, output_dtype)
    the_red.n_frames = n_frames

    return the_red.reduce(sckt)


def min(sckt: Socket,
        output_dtype: dtype = None) -> Socket:
    """
    Compute the minimum of a socket values.

    Args:
        sckt (Socket): input data
        output_dtype (dtype): output dtype

    Returns:
        Socket: minimum of socket values
    """
    return red(RType.MIN, sckt, output_dtype=output_dtype)


def max(sckt: Socket,
        output_dtype: dtype = None) -> Socket:
    """
    Compute the maximum value of a socket.

    Args:
        sckt (Socket): input data
        output_dtype (dtype): output dtype

    Returns:
        Socket: maximum value of a socket
    """
    return red(RType.MAX, sckt, output_dtype=output_dtype)


def sum(sckt: Socket,
        output_dtype: dtype = None) -> Socket:
    """
    Compute the sum of a socket.

    Args:
        sckt (Socket): input data
        output_dtype (dtype): output dtype

    Returns:
        Socket: sum of the socket
    """
    return red(RType.ADD, sckt, output_dtype=output_dtype)


def prod(sckt: Socket,
         output_dtype: dtype = None) -> Socket:
    """
    Compute the product of a socket values.

    Args:
        sckt (Socket): input data
        output_dtype (dtype): output dtype

    Returns:
        Socket: product of the socket values
    """
    return red(RType.MUL, sckt, output_dtype=output_dtype)


def all(sckt: Socket,
        output_dtype: dtype = None) -> Socket:
    """
    Return True if bool(x) is True for all values x in the socket.

    Args:
        sckt (Socket): input data
        output_dtype (dtype): output dtype

    Returns:
        Socket: True if bool(x) is True for all values x in the socket
    """
    return red(RType.AND, sckt, output_dtype=output_dtype)


def any(sckt: Socket,
        output_dtype: dtype = None) -> Socket:
    """
    Return True if bool(x) is True for at least one values x in the socket.

    Args:
        sckt (Socket): input data
        output_dtype (dtype): output dtype

    Returns:
        Socket: True if bool(x) = True for at least one values x in the socket.
    """
    return red(RType.OR, sckt, output_dtype=output_dtype)


__all__ = ['RType', 'red', 'min', 'max', 'sum', 'prod', 'all', 'any']