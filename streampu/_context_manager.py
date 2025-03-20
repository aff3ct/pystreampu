class _Context:
    def __init__(self, name):
        self.type = name
        self._mdl_stack = []
        self._firsts = []

    def store_module(self, mdl):
        self._mdl_stack.append(mdl)

    def store_task(self, tsk):
        self.store_module(tsk.module)
        if len(tsk.inputs) == 0 and all([s.has_data() for s in tsk.forwards]):
            self._firsts.append(tsk)


class _ContextManager:
    def __init__(self):
        self._opened_contexts = [_Context("Main")]
        self._closed_contexts = []

    @property
    def opened_contexts(self):
        return self._opened_contexts

    @property
    def closed_contexts(self):
        return self._closed_contexts

    @property
    def current_context(self):
        return self._opened_contexts[-1]

    def open_context(self, context):
        if context:
            self._opened_contexts.append(context)

    def close_context(self, context):
        if id(context) == id(self.current_context):
            self._closed_contexts.append(self._opened_contexts.pop(-1))

    def store_task(self, tsk):
        self.current_context.store_task(tsk)

    def store_module(self, mdl):
        self.current_context.store_module(mdl)


_context_manager = _ContextManager()

__all__ = ["_context_manager", "_Context"]
