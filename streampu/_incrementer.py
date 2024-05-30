# -*- coding: utf-8 -*-
import streampu._ext
from streampu._ext import int32


def incrementer(n_elmts: int, ns: int = 0, dtype: streampu._ext.dtype = int32):
    """Build an Incrementer.

    Args:
        n_elmts (int): socket size
        ns (int): sleep time in nanoseconds
        dtype (streampu._ext.dtype): data type

    Returns:
        out (Module): a new Incrementer

    Raises:
        TypeError: if dtype is not a valid dtype
    """
    if not isinstance(dtype, streampu._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an StreamPU datatype."
        raise TypeError(msg)
    class_name = f"Incrementer_{str(dtype)}"
    class_type = getattr(streampu._ext.inc, class_name)
    return class_type(n_elmts, ns)


__all__ = ["incrementer"]
