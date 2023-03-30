from ..builtins.core import Socket

import numpy as np

def socket_repr(sck):
    data_str = np.array(sck).__str__()
    str = f"socket({data_str}, dtype={sck.dtype.name}, name={sck.name}, task={sck.task.module.name}.{sck.task.name})"
    return str

Socket.__str__ = lambda s : np.array(s).__str__()
Socket.__repr__ = lambda s : socket_repr(s)

__all__ = ["Socket"]