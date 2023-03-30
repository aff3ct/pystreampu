from ..builtins.core import Module, Task, Socket
from typing import Union

def getattr_impl(cls:Module, attr:str)->Union[Task, Socket]:
    try:
        return cls[attr]
    except:
        raise AttributeError(f"'{cls.__class__.__name__}' object has no attribute '{attr}'")

Module.__getattr__ = getattr_impl

def dir_impl(cls:Module)->dict:
    from builtins import object
    new_dir = object.__dir__(cls)
    for t in cls.tasks:
        new_dir.append(t.name)
    return new_dir

Module.__dir__ = dir_impl

def setitem_impl(mdl:Module, str:str, sck:Socket)->None:
    mdl[str].bind(sck)

Module.__setitem__ = setitem_impl

__all__ = ["Module"]