from aff3ct import _ext

def uop(n_elmts:int, uop_name, TI = _ext.int8, TO = _ext.int8):
    """Return an AFF3CT unary operator module.

Parameters
----------
n_elmts : `int`
          input socket size
uop_name : `str`
           Name of the unary operator to instantiate
TI : `dtype`
     Input data type
TO : `dtype`
     Output data type

Returns
-------
out : AFF3CT module unary operator
"""
    if type(TI) is _ext.dtype:
        if type(TO) is _ext.dtype:
            uop_class_full = "Unaryop_" + uop_name + "_" + TI.name + "_" + TO.name
            uop = _ext.uop.__getattribute__(uop_class_full)(n_elmts)
            return uop
        else:
            raise TypeError("type '" + type(TO) + "' does not name an AFF3CT datatype.")
    else:
        raise TypeError("type '" + type(TI) + "' does not name an AFF3CT datatype.")