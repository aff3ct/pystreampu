from typing import Any
from aff3ct._ext.core import _Pipeline

class Pipeline(_Pipeline):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.original_modules = super().get_original_modules()

    def get_modules(self, module_class, set_modules=True):
        return_list = []
        for stage in self.stages:
            modules = stage.get_modules(module_class, set_modules)
            return_list.extend(modules)
        return return_list

    def __del__(self):
        self.unbind_adaptors()

__all__ = ["Pipeline"]
