from .. import builtins

def Unaryop(n_elmts, uop_name, TI = builtins.int8, TO = builtins.int8):
    if type(TI) is builtins.dtype:
        if type(TO) is builtins.dtype:
            uop_class_full = "Unaryop_" + uop_name + "_" + TI.name + "_" + TO.name
            uop = builtins.uop.__getattribute__(uop_class_full)(n_elmts)
            return uop
        else:
            raise TypeError("type '" + type(TO) + "' does not name an AFF3CT datatype.")
    else:
        raise TypeError("type '" + type(TI) + "' does not name an AFF3CT datatype.")