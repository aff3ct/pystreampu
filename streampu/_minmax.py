"""Create elementwize / binary min/max operators."""

from __future__ import annotations

from streampu._ext.core import Socket
from streampu._ext import dtype
from ._bop import min as bop_min, max as bop_max
from ._red import min as red_min, max as red_max


def min(s_0: Socket, *args: tuple[Socket, ...], output_dtype: dtype = None) -> Socket:

    if len(args) == 0:
        return red_min(s_0, output_dtype=output_dtype)

    min_ = s_0
    for arg in args:
        min_ = bop_min(min_, arg, output_dtype=output_dtype)
    return min_


def max(s_0: Socket, *args: tuple[Socket, ...], output_dtype: dtype = None) -> Socket:

    if len(args) == 0:
        return red_max(s_0, output_dtype=output_dtype)

    max_ = s_0
    for arg in args:
        max_ = bop_max(max_, arg, output_dtype=output_dtype)
    return max_
