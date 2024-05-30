# -*- coding: utf-8 -*-
"""Provides type hints."""

from __future__ import annotations

from typing import Union

import numpy as np

from ._ext.core import Socket

SocketLike = Union[Socket, np.array, list]
