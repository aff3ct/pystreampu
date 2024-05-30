# -*- coding: utf-8 -*-
"""Create elementwize / binary min/max operators."""

from __future__ import annotations

from streampu._ext import dtype
from streampu._ext.core import Socket

from ._bop import max as bop_max
from ._bop import min as bop_min
from ._red import max as red_max
from ._red import min as red_min


def min(*args: tuple[Socket, ...], output_dtype: dtype = None) -> Socket:
    """
    Compute the componentwise minimum of inputs.

    Args:
        *args (tuple[Socket, ...]): Tuple of sockets
        output_dtype(dtype): dtype of the output socket

    Returns:
        out(Socket): if *args has length 1, returns the minimum of the socket
                     if *args has length > 1, returns the componentwize minimum of all Sockets in args
    """
    if len(args) == 1:
        return red_min(args[0], output_dtype=output_dtype)

    min_ = args[0]
    for j in range(1, len(args)):
        min_ = bop_min(min_, args[j], output_dtype=output_dtype)
    return min_


def max(*args: tuple[Socket, ...], output_dtype: dtype = None) -> Socket:
    """
    Compute the componentwise maximum of inputs.

    Args:
        *args (tuple[Socket, ...]): Tuple of sockets
        output_dtype(dtype): dtype of the output socket

    Returns:
        out(Socket): if *args has length 1, returns the maximum of the socket
                     if *args has length > 1, returns the componentwize maximum of all Sockets in args
    """
    if len(args) == 1:
        return red_max(args[0], output_dtype=output_dtype)

    max_ = args[0]
    for j in range(1, len(args)):
        max_ = bop_max(max_, args[j], output_dtype=output_dtype)
    return max_
