r"Add some magic functions to :aff3ct._ext.core.Socket:"
import numpy as np

import aff3ct
from aff3ct._ext      import Slicer
from ._array          import array
from ._bop            import *
from ._uop            import *
from ._dtype          import int32

class Socket(aff3ct._ext.core.Socket):
    __slots__ = tuple()

    def __init__(self:"Socket"):
        super(aff3ct._ext.core.Socket, self).__init__()

    def numpy(self:"Socket")->np.array:
        return np.array(self)

    def __str__(self:"Socket")->str:
        """Get a str representing a socket."""
        return np.array(self).__str__()

    def __len__ (self:"Socket")->int:
        """Get the socket length."""
        return self.n_elmts//self.task.module.n_frames

    def __repr__(self:"Socket")->str:
        """Prints a socket."""
        data_str = self.__str__()
        str = f"socket({data_str}, dtype={self.dtype.name}, name={self.name}, task={self.task.module.name}.{self.task.name})"
        return str

    @classmethod
    def from_array(cls, input, dtype:aff3ct.dtype = None, n_frames:int = 1):
        """
        Creates a module with a task that produces the same data as in arr.

        Parameters
        ----------
        input : np.array, list
                input data

        dtype : aff3ct.dtype
                cast the data to dtype

        n_frames : int
                   Module number of frames
                   (Each frame will contain arr)

        Return
        ------
        out : aff3ct.Socket
              Socket containing the data.
        """
        try:
            arr = None
            if dtype:
                arr = np.array(input, dtype = np.dtype(dtype.name)) # Convert
            else:
                arr = np.array(input) # Convert
            so = array(arr, n_frames=n_frames) #.dtype.name
            so.__mdl__ = so.task.module
            so.__class__ = cls
        except:
            return NotImplemented # TODO : Error message
        return so

    def bind(self:"Socket", s_out, priority:int = 1) -> None:
        """
        Binds self to s_out. If s_out is not a `Socket`, s_out is converted to a `Socket` first.
        Parameters
        ----------
        s_out : SocketLike
                Socket to bind

        priority : int
                   Priority of the bind.
        """
        # The __tag__ attribute of module will store the modules which are binded to mdl
        mdl = self.task.module
        if not hasattr(mdl, "__tag__"):
            mdl.__tag__ = dict.fromkeys([tsk.name for tsk in mdl.tasks], {})

        if type(s_out) is not Socket:
            s_out = Socket.from_array(s_out)
        else:
            while hasattr(s_out, "__mrv__"):
                s_out = s_out.__mrv__

        mdl.__tag__[self.task.name][self.name] = s_out

        if self.direction == Socket.directions.FWD:
            # If slf is a forward socket, then it will be the most recent value of s_out
            s_out.__mrv__ = self

        self.__bind__(s_out, priority)

    #def __setitem__  (self, k, d)                       : ___setitem___  (self,k,d)
    #def __getitem__  (self, k)                          : ___getitem___  (self,k)

    @classmethod
    def _bop_factory(cls, name:str, s0:"Socket", s1:any, fwd = False, rev = False):
        """
        Binary operator factory from Sockets.
        Parameters
        ----------
        name : str
               Name of the Binary operator
        s0 : aff3ct.Socket
             First input of the binary operator (must be a Socket).
        s1 : aff3ct.Socket
             Second input of the binary operator.
        fwd : bool
              If true, performs operations in place.
        rev : bool
              If true, exchange s0 and s1.
        """
        n_frames = s0.task.module.n_frames
        TI = s0.dtype

        if type(s1) is not cls:
            s1 = cls.from_array(s1, dtype = s0.dtype, n_frames = n_frames)

        TO = TI
        if name in ["eq", "ge", "gt", "le", "lt", "ne"]:
            TO = int32

        n_in0 = s0.n_elmts//n_frames
        n_in1 = s1.n_elmts//n_frames

        the_bop = bop(n_in0, n_in1, name, TI, TO)
        the_bop.n_frames = n_frames

        if not rev and not fwd:
            s = the_bop.perform(s0,s1)
            return s
        elif rev and not fwd:
            s = the_bop.perform(s1,s0)
            return s
        else:
            the_bop.fwd_perform(s0,s1)
            return s0

    @classmethod
    def _uop_factory(cls, name, sckt, out_dtype=None):
        in_dtype = sckt.dtype
        if not out_dtype:
            out_dtype = in_dtype
        n_frames = sckt.task.module.n_frames
        n_elmts = sckt.n_elmts
        the_uop = uop(n_elmts//n_frames, name, in_dtype, out_dtype)
        the_uop.n_frames = sckt.task.module.n_frames
        s = the_uop.perform(sckt)
        return s

    def __setitem__(self, key, data):
        slc = None
        if type(key) is slice:
            start, stop, step = key.indices(self.n_elmts // self.task.module.n_frames)
            slc = Slicer(self, np.arange(start, stop, step))
        elif type(key) is int:
            slc = Slicer(self, key)

        slc.n_frames = self.task.module.n_frames
        if hasattr(data,"__len__") and len(data) > 1:
            slc.write(self, data)
        else:
            slc.write_one(self, data)

        #TODO : fix this
        if not hasattr(self, "__slicers__"):
            self.__slicers__ = []
        self.__slicers__.append(slc)

    def __getitem__(self:"Socket", key:slice|int):
        slc = None
        if type(key) is slice:
            start, stop, step = key.indices(self.n_elmts // self.task.module.n_frames)
            slc = Slicer(self, np.arange(start, stop, step))
        elif type(key) is int:
            slc = Slicer(self, key)

        slc.n_frames = self.task.module.n_frames

        #TODO : fix this
        if not hasattr(self, "__slicers__"):
            self.__slicers__ = []
        self.__slicers__.append(slc)

        return slc.read(self)

    def __add__(self, value):
        """Return self + s."""
        return Socket._bop_factory("add", self, value)

    def __iadd__(self, value):
        """Return self += value."""
        return Socket._bop_factory("add", self, value, fwd=True)

    def __radd__(self, value):
        """Return value + self."""
        return Socket._bop_factory("add", self, value, rev=True)

    def __sub__(self, value):
        """Return self - s."""
        return Socket._bop_factory("sub", self, value)

    def __isub__(self, value):
        """Return self -= value."""
        return Socket._bop_factory("sub", self, value, fwd=True)

    def __rsub__(self, value):
        """Return value - self."""
        return Socket._bop_factory("sub", self, value, rev=True)

    def __mul__(self, value):
        """Return self * s."""
        return Socket._bop_factory("mul", self, value)

    def __imul__(self, value):
        """Return self *= value."""
        return Socket._bop_factory("mul", self, value, fwd=True)

    def __rmul__(self, value):
        """Return value * self."""
        return Socket._bop_factory("mul", self, value, rev=True)

    def __truediv__(self, value):
        """Return self / s."""
        return Socket._bop_factory("div", self, value)

    def __itruediv__(self, value):
        """Return self /= value."""
        return Socket._bop_factory("div", self, value, fwd=True)

    def __rtruediv__(self, value):
        """Return value / self."""
        return Socket._bop_factory("div", self, value, rev=True)

    def __ge__(self, value):
        """Return self >= s."""
        return Socket._bop_factory("ge", self, value)

    def __rge__(self, value):
        """Return value >= self."""
        return Socket._bop_factory("ge", self, value, rev=True)

    def __gt__(self, value):
        """Return self > s."""
        return Socket._bop_factory("gt", self, value)

    def __rgt__(self, value):
        """Return value > self."""
        return Socket._bop_factory("gt", self, value, rev=True)

    def __eq__(self, value):
        """Return self == s."""
        return Socket._bop_factory("eq", self, value)

    def __req__(self, value):
        """Return value == self."""
        return Socket._bop_factory("eq", self, value, rev=True)

    def __neq__(self, value):
        """Return self != s."""
        return Socket._bop_factory("neq", self, value)

    def __rneq__(self, value):
        """Return value != self."""
        return Socket._bop_factory("neq", self, value, rev=True)

    def __le__(self, value):
        """Return self <= s."""
        return Socket._bop_factory("le", self, value)

    def __rle__(self, value):
        """Return value <= self."""
        return Socket._bop_factory("le", self, value, rev=True)

    def __lt__(self, value):
        """Return self < s."""
        return Socket._bop_factory("lt", self, value)

    def __rlt__(self, value):
        """Return value < self."""
        return Socket._bop_factory("lt", self, value, rev=True)

    def __and__(self, value):
        """Return self & s."""
        return Socket._bop_factory("and", self, value)

    def __iand__(self, value):
        """Return self &= value."""
        return Socket._bop_factory("and", self, value, fwd=True)

    def __rand__(self, value):
        """Return value & self."""
        return Socket._bop_factory("and", self, value, rev=True)

    def __or__(self, value):
        """Return self | s."""
        return Socket._bop_factory("or", self, value)

    def __ior__(self, value):
        """Return self |= value."""
        return Socket._bop_factory("or", self, value, fwd=True)

    def __ror__(self, value):
        """Return value | self."""
        return Socket._bop_factory("or", self, value, rev=True)

    def __xor__(self, value):
        """Return self ^ s."""
        return Socket._bop_factory("xor", self, value)

    def __ixor__(self, value):
        """Return self ^= value."""
        return Socket._bop_factory("xor", self, value, fwd=True)

    def __rxor__(self, value):
        """Return value ^ self."""
        return Socket._bop_factory("xor", self, value, rev=True)

    def __abs__(self):
        """Return |self|."""
        return Socket._uop_factory("abs", self)

    def __neg__(self):
        """Return -self."""
        return Socket._uop_factory("neg", self)

    def __invert__(self):
        """Return ~self."""
        return Socket._uop_factory("not", self)

    def astype(self, dtype):
        """Return a cast of self as dtype."""
        return Socket._uop_factory("cast", self, dtype)

    #Socket.astype       = lambda slf,dt : cast           (slf, dt)

def add            (s0:Socket, s1:Socket): return Socket.bop_factory("add",s0,s1)
def sub            (s0:Socket, s1:Socket): return Socket.bop_factory("sub",s0,s1)
def mul            (s0:Socket, s1:Socket): return Socket.bop_factory("mul",s0,s1)
def div            (s0:Socket, s1:Socket): return Socket.bop_factory("div",s0,s1)
def greater_equal  (s0:Socket, s1:Socket): return Socket.bop_factory( "ge",s0,s1)
def greater        (s0:Socket, s1:Socket): return Socket.bop_factory( "gt",s0,s1)
def equal          (s0:Socket, s1:Socket): return Socket.bop_factory( "eq",s0,s1)
def not_equal      (s0:Socket, s1:Socket): return Socket.bop_factory("neq",s0,s1)
def less_equal     (s0:Socket, s1:Socket): return Socket.bop_factory( "le",s0,s1)
def less           (s0:Socket, s1:Socket): return Socket.bop_factory( "lt",s0,s1)
def bitwise_and    (s0:Socket, s1:Socket): return Socket.bop_factory("and",s0,s1)
def bitwise_or     (s0:Socket, s1:Socket): return Socket.bop_factory( "or",s0,s1)
def bitwise_xor    (s0:Socket, s1:Socket): return Socket.bop_factory("xor",s0,s1)
def abs            (s : Socket):
    """Compute the absolute value of the elements of a Socket.
Parameters
----------
s : :Socket:
    Socket containing input data.

Returns
-------
out : :Socket:
      Socket containing output data.
"""
    return Socket.uop_factory("abs",s)

def neg (s):
    """Compute the absolute value of the elements of a Socket.
Parameters
----------
s : :Socket:
    Socket containing input data.

Returns
-------
out : :Socket:
      Socket containing output data.
"""
    return Socket.uop_factory("neg",s)

def bitwise_not(s): return Socket.uop_factory("not",s)
def cast(s, dtype): return Socket.uop_factory("cast",s, dtype)

__all__ = ['Socket', 'add', 'sub', 'mul',
           'div', 'greater_equal', 'greater', 'equal', 'not_equal', 'less_equal',
           'less', 'bitwise_and', 'bitwise_or', 'bitwise_xor',
           "uop", "abs", "neg", "cast", "bitwise_not"]

