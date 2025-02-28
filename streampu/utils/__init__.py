import os.path as _osp

import pybind11 as _p11

import streampu as _spu


def get_cmake_dirs():
    p11_cmake_path = _osp.dirname(_p11.get_cmake_dir())
    spu_cmake_path = _osp.join(_osp.dirname(_spu._ext.__file__), "lib", "cmake")
    return p11_cmake_path + ":" + spu_cmake_path


__all__ = ["get_cmake_dirs"]
