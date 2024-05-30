# -*- coding: utf-8 -*-
from __future__ import annotations

from typing import List, Union

from streampu._ext import exceptions
from streampu._ext.core import Socket, _Sequence
from streampu._ext.set import Set


def _unique(in_list: list):
    out_list = []
    for elt in in_list:
        if id(elt) not in [id(e) for e in out_list]:
            out_list.append(elt)
    return out_list


def _get_firsts(s: Socket):
    def visit(s: Socket, visited: List[Socket]):
        tsk = s.task
        visited.append(tsk)

        if len(tsk.inputs) == 0 and len(tsk.forwards) == 0 and not tsk.is_bound():
            return [tsk]

        out = []
        lbnd = _unique([si.bound_socket for si in tsk.inputs])
        lbnd += _unique([si.bound_socket for si in tsk.forwards])
        for b in lbnd:
            try:
                if b.task not in visited:
                    lt = visit(b, visited)
                    for t in lt:
                        out.append(t)
            except Exception:
                out.append(b.task)
        return out

    return visit(s, [])


def get_cloned_modules(self, module_ref):
    found = False
    mid = 0
    all_modules = self.get_modules_per_threads()
    while mid < len(all_modules[0]) and not found:
        if id(all_modules[0][mid]) == id(module_ref):
            found = True
        else:
            mid += 1
    if not found:
        raise (exceptions.RuntimeError("'module_ref' can't be found in the sequence."))

    cloned_modules = []
    for tid in range(len(all_modules)):
        if isinstance(all_modules[tid][mid], type(module_ref)):
            cloned_modules.append(all_modules[tid][mid])
        else:
            raise exceptions.RuntimeError("This should never happen.")

    return cloned_modules


_Sequence.get_cloned_modules = get_cloned_modules


def get_modules(self, module_class, set_modules=True):
    all_modules = [m for lst in self.get_modules_per_threads() for m in lst]
    return_list = [m for m in all_modules if isinstance(m, module_class)]
    if set_modules:
        sse_list = [mdl for mdl in all_modules if isinstance(mdl, Set)]
        for sse in sse_list:
            return_list += sse.sequence.get_module(module_class, True)
    return return_list


_Sequence.get_modules = get_modules


class Sequence(_Sequence):
    """Overlay of streampu._ext.core._Sequence."""

    def __init__(self, *args, **kwargs):
        """Build a Pipeline.

        Args:
            *args: Variable length argument list.
            **kwargs: Arbitrary keyword arguments.
        """
        super().__init__(*args, **kwargs)
        self.original_modules = super().get_modules_per_threads()[0]

    @staticmethod
    def from_socket(sockets=Union[Socket, List[Socket]], *args: tuple, **kwargs: dict):
        """Build a Sequence from a list of sockets or a sockedt.

        Args:
            sockets(Socket|List[Socket]): A list of socket
            *args: Variable length argument list.
            **kwargs: Arbitrary keyword arguments.

        Returns:
            out (Sequence): A Sequence that writes the sockets
        """
        firsts = []
        if not isinstance(sockets, list):
            sockets = [sockets]
        for s_itm in sockets:
            while hasattr(s_itm, "_mrv"):
                s_itm = s_itm._mrv
            local_firsts = _get_firsts(s_itm)
            for first in local_firsts:
                if first not in firsts:
                    firsts.append(first)
        return Sequence(firsts, [], [], *args, **kwargs)


__all__ = ["Sequence"]
