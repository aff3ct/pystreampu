import aff3ct._ext
from aff3ct._ext import dtype, int8, int32

from aff3ct._ext.core import Module

def bop(n_in0:int, n_in1:int, bop_name:str, TI:dtype = int8, TO:dtype = int8) -> Module:
    """Return a binary operator module.

Parameters
----------
n_in1 : `int`
        Number of elements of input socket in0
n_in2 : `int`
        Number of elements of input socket in1
bop_name : `str`
           Name of the binary operator to instantiate
TI : `dtype`
     Input data type
TO : `dtype`
     Output data type

Returns
-------
out : AFF3CT module binary operator
"""
    if type(TI) is dtype:
        if type(TO) is dtype:
            try:
                return aff3ct._ext.bop.__getattribute__("Binaryop_" + bop_name + "_" + TI.name + "_" + TO.name)(n_in0, n_in1)
            except:
                str = "binary operator '" + bop_name + "' does not exist for input type '" + TI.name + "."
                raise TypeError(str)
        else:
            raise TypeError("type '" + type(TO) + "' does not name an AFF3CT datatype.")
    else:
        raise TypeError("type '" + type(TI) + "' does not name an AFF3CT datatype.")
