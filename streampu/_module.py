# -*- coding: utf-8 -*-
"""Add some python magic dedicated to streampu._ext.core.Module."""

from __future__ import annotations

from typing import Union

from streampu._ext.core import Module, Socket, Task

from ._typing import SocketLike


def _call_impl(
    self: Module,
    *args: tuple[SocketLike],
    raw_data=False,
    no_doc=False,
    **kwargs: dict[str, SocketLike],
) -> Union[Socket, tuple[Socket], None]:
    return self.tasks[0](*args, raw_data=raw_data, no_doc=no_doc, **kwargs)


def getattr_impl(self: Module, attr: str) -> Union[Task, Socket]:
    """Overload __getattr__ of streampu._ext.core.Module.

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


def setitem_impl(self: Module, attr: str, tsk_sck: Task | Socket) -> None:
    """Bind self[attr] to the socket sck.

    Args:
        self (Module): A Module
        attr (str): attribute name (should name a task or a socket)
        tsk_sck (Task|Socket): socket to bind self[attr].
    """
    self[attr].bind(tsk_sck)


Module.__call__ = _call_impl
Module.__getattr__ = getattr_impl
Module.__dir__ = dir_impl
Module.__setitem__ = setitem_impl

__all__ = ["Module"]
