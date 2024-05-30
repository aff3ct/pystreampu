# -*- coding: utf-8 -*-
import streampu._ext
from streampu._ext import int32


def initializer(n_elmts: int, dtype: streampu._ext.dtype = int32):
    """Build an Initializer.

    Args:
        n_elmts (int): socket size
        dtype (streampu._ext.dtype): data type

    Returns:
        out (Module): a new Initializer

    Raises:
        TypeError: if dtype is not a valid dtype
    """
    if not isinstance(dtype, streampu._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an StreamPU datatype."
        raise TypeError(msg)
    class_name = f"Initializer_{str(dtype)}"
    class_type = getattr(streampu._ext.ini, class_name)
    return class_type(n_elmts)


__all__ = ["initializer"]
