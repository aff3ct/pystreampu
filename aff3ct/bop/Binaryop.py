from .. import builtins
import numpy as np

def Binaryop(n_in1:int, n_in2:int, bop_name:str, TI:builtins.dtype = builtins.int8, TO:builtins.dtype = builtins.int8):
    if type(TI) is builtins.dtype:
        if type(TO) is builtins.dtype:
            try:
                return builtins.bop.__getattribute__("Binaryop_" + bop_name + "_" + TI.name + "_" + TO.name)(n_in1, n_in2)
            except:
                str = "binary operator '" + bop_name + "' does not exist for input type '" + TI.name + "."
                raise TypeError(str)
        else:
            raise TypeError("type '" + type(TO) + "' does not name an AFF3CT datatype.")
    else:
        raise TypeError("type '" + type(TI) + "' does not name an AFF3CT datatype.")
