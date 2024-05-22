from __future__ import annotations

import aff3ct._ext
from aff3ct._ext import int32


def delayer(size: int, init_val: int | float, dtype: aff3ct._ext.dtype = int32):
    if not isinstance(dtype, aff3ct._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)
    class_name = f"Delayer_{str(dtype)}"
    class_type = getattr(aff3ct._ext.dly, class_name)
    return class_type(size, init_val)


__all__ = ["delayer"]
