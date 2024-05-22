"""Provides type hints."""

from __future__ import annotations

from typing import Union

from ._ext.core import Socket

import numpy as np

SocketLike = Union[Socket, np.array, list]
