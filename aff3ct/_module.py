
"""Add some python magic dedicated to aff3ct._ext.core.Module."""

from __future__ import annotations

from typing import Union

from aff3ct._ext.core import Module, Socket, Task


def getattr_impl(self: Module, attr: str) -> Union[Task, Socket]:
    """Overload __getattr__ of aff3ct._ext.core.Module.

    module[task_name] will return the task named `task_name` of the module.

    module[task_name::socket_name] will return the socket named `socket_name`
    of the task `task_name` of the module.

    Args:
        self (Module): A Module
        attr (str): attribute name

    Returns:
        out (Task): if attr is formatted as 'task_name'
        out (Socket): if attr is formatted as 'task_name::socket_name'

    """
    if attr in [t.name for t in self.tasks]:
        return self[attr]

    return object.__getattribute__(self, attr)


def dir_impl(self: Module) -> dict:
    """Add tasks of a module to its __dir__.

    Args:
        self (Module): A Module

    Returns:
        out (dict): task augmented Module's dict
    """
    new_dir = object.__dir__(self)
    for tsk in self.tasks:
        new_dir.append(tsk.name)
    return new_dir


def setitem_impl(self: Module, attr: str, sck: Socket) -> None:
    """Bind self[attr] to the socket sck.

    Args:
        self (Module): A Module
        attr (str): attribute name (should name a task or a socket)
        sck (Socket): socket to bind self[attr].
    """
    self[attr].bind(sck)


Module.__getattr__ = getattr_impl
Module.__dir__ = dir_impl
Module.__setitem__ = setitem_impl

__all__ = ['Module']
