from .. import builtins
from .Unaryop import Unaryop

def uop_generic_factory(name, sckt, out_dtype=None):
    in_dtype = sckt.dtype
    if not out_dtype:
        out_dtype = in_dtype
    n_frames = sckt.task.module.n_frames
    n_elmts = sckt.n_elmts
    the_uop = Unaryop(n_elmts//n_frames, name, in_dtype, out_dtype)
    the_uop.n_frames = sckt.task.module.n_frames
    s = the_uop.perform(sckt)
    return s

Socket = builtins.core.Socket
Socket.__neg__    = lambda slf       : uop_generic_factory("neg",  slf)
Socket.astype     = lambda slf,dtype : uop_generic_factory("cast", slf, dtype)
Socket.__invert__ = lambda slf       : uop_generic_factory("not",  slf)

def abs (s):        return uop_generic_factory("abs",s)
def neg (s):        return uop_generic_factory("neg",s)
def cast(s, dtype): return uop_generic_factory("cast",s, dtype)

all = ["abs","neg","cast"]