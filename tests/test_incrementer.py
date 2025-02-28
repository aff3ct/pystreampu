# -*- coding: utf-8 -*-
"""Functionnal tests for Incrementer."""

import streampu as spu
from streampu import uint32

n_elts = 5


def test_incrementer(dtype):
    src = spu.source_random(n_elts, dtype=dtype)
    spu.help(src)

    print(src["generate::out_data"])
    src["generate"].exec()

    incr = spu.incrementer(n_elts, dtype=dtype)
    spu.help(incr)

    incr["increment::in"] = src["generate::out_data"]

    for i in range(0, 4):
        src["generate"].exec()
        incr["increment"].exec()
        print("Output of source:", src["generate::out_data"])
        print("Output of incrementer:", incr["increment::out"])


if __name__ == "__main__":
    test_incrementer(uint32)
