from aff3ct._ext.core import Pipeline


def get_modules(self, module_class, subsequence_modules=True):
    return_list = []
    for stage in self.stages:
        modules = stage.get_modules(module_class, subsequence_modules)
        return_list.extend(modules)
    return return_list


Pipeline.get_modules = get_modules


__all__ = ["Pipeline"]
