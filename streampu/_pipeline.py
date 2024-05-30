# -*- coding: utf-8 -*-
from streampu._ext.core import _Pipeline


class Pipeline(_Pipeline):
    """Overlay of streampu._ext.core._Pipeline."""

    def __init__(self, *args, **kwargs):
        """Build a Pipeline.

        Args:
            *args: Variable length argument list.
            **kwargs: Arbitrary keyword arguments.
        """
        super().__init__(*args, **kwargs)
        self.original_modules = super().get_original_modules()

    def __del__(self):
        """Destructor."""
        self.unbind_adaptors()

    def get_modules(self, module_class: type, set_modules: bool = True) -> list:
        """Return the list of modules of a given class.

        Args:
            module_class(type): a module class type
            set_modules(bool): if True consider 'set' as modules, else explore the content of the set

        Returns:
            out (list): list of modules with type `module_class`
        """
        return_list = []
        for stage in self.stages:
            modules = stage.get_modules(module_class, set_modules)
            return_list.extend(modules)
        return return_list


__all__ = ["Pipeline"]
