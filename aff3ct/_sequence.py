from __future__ import annotations

from typing import Union, List

from aff3ct._ext import exceptions
from aff3ct._ext.core import Sequence, Socket
from aff3ct._ext.sse import Subsequence


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
        raise(exceptions.RuntimeError("'module_ref' can't be found in the sequence."))

    cloned_modules = []
    for tid in range(len(all_modules)):
        if isinstance(all_modules[tid][mid], type(module_ref)):
            cloned_modules.append(all_modules[tid][mid])
        else:
            raise exceptions.RuntimeError("This should never happen.")

    return cloned_modules


Sequence.get_cloned_modules = get_cloned_modules


def get_modules(self, module_class, subsequence_modules=True):
    all_modules = [m for lst in self.get_modules_per_threads() for m in lst]
    return_list = [m for m in all_modules if isinstance(m, module_class)]
    if subsequence_modules:
        sse_list = [mdl for mdl in all_modules if isinstance(mdl, Subsequence)]
        for sse in sse_list:
            return_list += sse.sequence.get_module(module_class, True)
    return return_list


Sequence.get_modules = get_modules


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
        else:
            out = []
            lbnd = _unique([si.bound_socket for si in tsk.inputs])
            lbnd += _unique([si.bound_socket for si in tsk.forwards])
            for b in lbnd:
                try:
                    if b.task not in visited:
                        lt = visit(b, visited)
                        for t in lt:
                            out.append(t)
                except Exception as exc:
                    print(exc)
                    out.append(b.task)
        return out
    return visit(s, [])


def from_socket(sockets = Union[Socket, List[Socket]], *args: tuple, **kwargs: dict):
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


Sequence.from_socket = from_socket
__all__ = ["Sequence"]
