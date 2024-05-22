from __future__ import annotations

import streampu._ext
from streampu._ext import int32


def delayer(size: int, init_val: int | float, dtype: streampu._ext.dtype = int32):
    if not isinstance(dtype, streampu._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an StreamPU datatype."
        raise TypeError(msg)
    class_name = f"Delayer_{str(dtype)}"
    class_type = getattr(streampu._ext.dly, class_name)
    return class_type(size, init_val)


__all__ = ["delayer"]
