from .. import builtins

def Unaryop(n_elmts, uop_name, TI = builtins.int8, TO = builtins.int8):
    if issubclass(TI, builtins.generic):
        if issubclass(TO, builtins.generic):
            uop_class_full = "Unaryop_" + uop_name + "_" + TI.name() + "_" + TO.name()
            return builtins.uop.__getattribute__(uop_class_full)(n_elmts)
        else:
            raise TypeError("type '" + type(TO) + "' does not name an AFF3CT datatype.")
    else:
        raise TypeError("type '" + type(TI) + "' does not name an AFF3CT datatype.")