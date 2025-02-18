# -*- coding: utf-8 -*-
from streampu._ext.sfl import Stateful

Stateful.__doc__ = R"""
Class Stateful

Stateful modules are modules that cannot be cloned due to internal state.
"""

__all__ = ["Stateful"]
