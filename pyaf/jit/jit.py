from .. import builtins
from copy import deepcopy
import ast
import inspect
import numpy as np

node_to_bop = {
    'And'     : 'and',
    'Or'      : 'or',
    'BitXor'  : 'xor',
    'BitAnd'  : 'and',
    'BitOr'   : 'or',
    'Eq'      : 'eq',
    'Lt'      : 'lt',
    'LtE'     : 'le',
    'Gt'      : 'gt',
    'GtE'     : 'ge',
    'NotEq'   : 'ne',
    'Add'     : 'add',
    'Sub'     : 'sub',
    'Mult'    : 'mul',
    'Div'     : 'div',
    'FloorDiv': 'div'
}

bop_to_label = {
    'And'     : '&&',
    'Or'      : '||',
    'BitXor'  : '^',
    'BitAnd'  : '&',
    'BitOr'   : '|',
    'Eq'      : '==',
    'Lt'      : '<',
    'LtE'     : '<=',
    'Gt'      : '>',
    'GtE'     : '>=',
    'NotEq'   : '!=',
    'Add'     : '+',
    'Sub'     : '-',
    'Mult'    : '*',
    'Div'     : '/',
    'FloorDiv': '//'
}

class Visitor(ast.NodeVisitor):
    def __init__(self, func, locals = {}, auto_loop=False, n_threads=1, debug=False, debug_limit=-1, stats = False):
        super().__init__()
        self.binding =  []

        self.func = func
        self.func_args = None
        self.func_kwargs = None

        self.init_locals = locals.copy()
        self.locals = locals.copy()
        self.local_modules = {}
        self.loop_firsts = []
        self.firsts = []
        self.sequence = None
        self.last_socket = None
        self.returned_sckts = None
        self.n_threads = n_threads
        self.auto_loop = auto_loop
        self.debug = debug
        self.debug_limit = debug_limit
        self.stats = stats

    def set_func_args(self, func_args, func_kwargs):
        has_changed = False
        if func_args != self.func_args:
            self.func_args   = func_args
            has_changed = True
        if func_kwargs != self.func_kwargs:
            self.func_kwargs = func_kwargs
            has_changed = True
        return has_changed

    def visit_FunctionDef(self, node):
        node_cpy = deepcopy(node)
        node_cpy.body = [ast.parse('return locals()', mode='exec').body]
        node_cpy.name = 'get_locals'
        local = {}
        exec(ast.unparse(node_cpy), self.func.__globals__, local)
        if self.func_args and self.func_kwargs:
            self.locals = local["get_locals"](*self.func_args, **self.func_kwargs)
        elif self.func_args and not self.func_kwargs:
            self.locals = local["get_locals"](*self.func_args)
        elif not self.func_args and self.func_kwargs:
            self.locals = local["get_locals"](**self.func_kwargs)
        else:
            self.locals = local["get_locals"]()
        self.generic_visit(node)

    def checked_obj(self, code, type_, locals={}):
        # Eval code and check output type
        obj = eval(code, self.func.__globals__, locals)
        if type(obj) is not type_ and not issubclass(type(obj), type_):
            return None
        return obj

    def get_socket_from_node(self, node):
        # Function that returns the socket represented by the node.
        # Attributes
        # ----------
        # node : a node of type ast.Name, ast.Constant, or subclassing of ast.expr
        #
        # Returns
        # -------
        # Returns either a socket or a np.ndarray or a constant depending on the type of node. Returns None if the expression neither these three outputs can be determined.
        returned_socket = None
        var = None
        if type(node) is ast.Name:
            var_name = node.id
            if var_name in self.locals:
                var = self.locals[var_name]
            elif var_name in self.func.__globals__:
                var = self.func.__globals__[var_name]

        elif type(node) is ast.Constant:
            var = node.value
        elif issubclass(type(node), ast.expr):
            var = self.visit(node)
            if type(var) is list:
                if len(var) < 1:
                    print("Issue! <1") #TODO improve message
                if len(var) > 1:
                    print("Issue! >1") #TODO improve message
                var = var[0]
        else:
            print(node) #TODO improve message

        if type(var) is builtins.core.Socket or type(var) is np.ndarray or type(var) is int or type(var) is float:
            returned_socket = var
        else:
            print(type(var))

        return returned_socket

    def visit_Call(self, node):
        # Function that visits an AST Call node.
        # In this "compiler" calls represent tasks binding.
        # Attributes
        # ----------
        # node : an AST Call node
        #
        # Returns
        # -------
        # The list of output sockets for the called task.

        node_code = ast.unparse(node.func)
        tsk = self.checked_obj(node_code, builtins.core.Task, self.locals)
        if tsk:
            input_nbr = 0
            for i in range(len(node.args)):
                self.visit(node.args[i])
                sck_out = self.get_socket_from_node(node.args[i])
                self.binding.append([sck_out,tsk.sockets[i]])
                input_nbr += 1

            for kw in node.keywords:
                self.visit(kw.value)
                sck_out = self.get_socket_from_node(node.args[i])
                self.binding.append([sck_out,tsk[kw.arg]])
                input_nbr += 1
            if input_nbr == 0:
                self.firsts.append(tsk)

            return tsk.outputs[0:len(tsk.outputs)-1]
        #elif self.checked_obj(node_code, pyaf.module.Module, self.locals):
        #    pass
        else:
            print('\033[93m' + 'Line number ' + str(node.lineno) + " is not AFF3CT compatible, it wont't be compiled : \n '" + node_code + '"\033[0m')

        return self.generic_visit(node)

    def visit_If(self, node):
        # Function that visits an AST If node.
        # From the node, it creates a pyaf.module.switcher.Switcher module and create its binding.
        #
        # Attributes
        # ----------
        # node : an AST If node
        body_visitor   = Visitor(self.func, self.locals)
        for n in node.body:
            body_visitor.visit(n)

        orelse_visitor = Visitor(self.func, self.locals)
        for n in node.orelse:
            orelse_visitor.visit(n)

        cnd_sck = self.get_socket_from_node(node.test)

        common_inputs  = [s for s in [b[0] for b in body_visitor.binding] if id(s) in [id(s) for s in [b[0] for b in orelse_visitor.binding]]]
        common_inputs  = [s for s in common_inputs if type(s) is builtins.core.Socket]
        common_outputs = []
        output_socket_key = ""
        for key in body_visitor.locals:
            if key in  orelse_visitor.locals and not key in self.locals:
                common_outputs.append([body_visitor.locals[key], orelse_visitor.locals[key]])
                output_socket_key = key
        switcher = builtins.swi.Switcher(2,
                                                      common_inputs [0].n_elmts,
                                                      common_inputs [0].dtype,
                                                      common_outputs[0][0].n_elmts,
                                                      common_outputs[0][0].dtype
                                                      )
        # put switcher in list
        self.local_modules["switcher_" + str(id(switcher))] = switcher
        self.local_modules.update(body_visitor.local_modules)
        self.local_modules.update(orelse_visitor.local_modules)

        # bind body
        self.binding.append([cnd_sck, switcher.commute.ctrl])
        self.binding.append([common_inputs[0], switcher.commute.data])
        for bind in body_visitor.binding:
            if id(bind[0]) == id(common_inputs[0]):
                self.binding.append([switcher.commute.data1, bind[1]])
            else:
                self.binding.append(bind)

        # bind orelse
        for bind in orelse_visitor.binding:
            if id(bind[0]) == id(common_inputs[0]):
                self.binding.append([switcher.commute.data0, bind[1]])
            else:
                self.binding.append(bind)

        self.binding.append([common_outputs[0][0],switcher.select.data1])
        self.binding.append([common_outputs[0][1],switcher.select.data0])

        self.locals[output_socket_key] = switcher.select.data

    def visit_For(self, node):
        iter = self.checked_obj(ast.unparse(node.iter), builtins.core.Module, self.locals)

        if type(iter) is builtins.Range:
            iter.throw_to_stop = False
            self.local_modules["range_"    + str(id(iter))    ] = iter
            if type(node.target) is ast.Name:
                self.locals[node.target.id] = iter.iterate.it
            else:
                pass
                # TODO : message d'erreur

            body_visitor   = Visitor(self.func, self.locals)
            for n in node.body:
                body_visitor.visit(n)

            loop_inputs  = [s for s in [b[0] for b in body_visitor.binding]]
            loop_inputs  = [s for s in loop_inputs if id(s) in [id(s) for s in self.locals.values()]]
            loop_inputs  = [s for s in loop_inputs if type(s) is builtins.core.Socket]
            loop_input = loop_inputs[0]
            input_key = [k for k, v in self.locals.items() if id(v) == id(loop_input)][0]


            switcher = builtins.swi.Switcher(2,
                                                          loop_input.n_elmts,
                                                          loop_input.dtype
                                                          )

            self.loop_firsts.append(switcher.select)
            self.local_modules["switcher_" + str(id(switcher))] = switcher
            self.local_modules.update(body_visitor.local_modules)

            most_recent_input = body_visitor.locals[input_key]

            self.binding.append([loop_input, switcher.select.data1])
            self.binding.append([switcher.select.data, switcher.commute.data])
            self.binding.append([switcher.select.status, iter.iterate])
            self.binding.append([iter.iterate.flg, switcher.commute.ctrl])

            for bind in body_visitor.binding:
                if id(bind[0]) == id(loop_input):
                    self.binding.append([switcher.commute.data0, bind[1]])
                else:
                    self.binding.append(bind)
            self.binding.append([most_recent_input, switcher.select.data0])
            self.locals[input_key] = switcher.commute.data1

            # TODO: error message if len(inputs)>1
        else:
          raise SyntaxError("\033[91m Unhandled type of for loop.\033[0m")

    def create_bop(self, bop_nodetype, lhs, rhs):
        bop_type = node_to_bop[bop_nodetype]
        prev_task = None
        if type(lhs) == builtins.core.Socket:
            datatype = lhs.dtype.name
            n_elmts   = lhs.n_elmts//lhs.task.module.n_frames
            prev_task = lhs.task
            if type(rhs) is not builtins.core.Socket:
                rhs      = lhs.dtype.numpy(rhs)
        elif type(rhs) is builtins.core.Socket:
            datatype = rhs.dtype.name
            n_elmts  = rhs.n_elmts//rhs.task.module.n_frames
            prev_task = rhs.task
            lhs      = rhs.dtype.numpy(lhs)
        else:
            raise SyntaxError("\033[91m Wrong input type for binary operator.\033[0m")

        bop = builtins.bop.__getattribute__('Binaryop_' + bop_type + '_' + datatype + '_' + datatype)(n_elmts)
        bop.name = bop_to_label[bop_nodetype]
        self.local_modules["bop_" + bop_type + "_" + str(id(bop))]= bop
        self.binding.append([lhs, bop.perform.in1])
        self.binding.append([rhs, bop.perform.in2])

        return bop

    def visit_Compare(self, node):
        bopnode_type = node.ops[0].__class__.__name__
        lhs = self.get_socket_from_node(node.left)
        rhs = self.get_socket_from_node(node.comparators[0])
        bop = self.create_bop(bopnode_type,lhs,rhs)
        return [bop.perform.out]

    def visit_BinOp(self, node):
        bopnode_type = node.op.__class__.__name__
        lhs = self.get_socket_from_node(node.left)
        rhs = self.get_socket_from_node(node.right)
        bop = self.create_bop(bopnode_type,lhs,rhs)
        return [bop.perform.out]

    def visit_BoolOp(self, node):
        bopnode_type = node.op.__class__.__name__
        lhs = self.get_socket_from_node(node.values[0])
        rhs = self.get_socket_from_node(node.values[1])
        bop = self.create_bop(bopnode_type,lhs,rhs)
        return [bop.perform.out]

    def visit_Subscript(self, node):
        lst = self.visit(node.value)
        if type(lst) is list:
            if type(node.slice) is ast.Slice:
                lower = None
                if node.slice.lower:
                    lower = eval(ast.unparse(node.slice.lower))
                upper = None
                if node.slice.upper:
                    upper = eval(ast.unparse(node.slice.upper))
                step = None
                if node.slice.step:
                    step = eval(ast.unparse(node.slice.step))

                return lst[slice(lower,upper,step)]
            elif type(node.slice) is ast.Constant:
                return [lst[node.slice.value]]
        else:
            return self.generic_visit(node)

    def visit_Assign(self, node):
        socket_list = self.visit(node.value)
        list_of_names = []
        if type(node.targets[0]) is ast.Tuple or type(node.targets[0]) is ast.List:
            for elt in node.targets[0].elts:
                list_of_names.append(elt.id)
        else : # if it is a name
            list_of_names = [node.targets[0].id]

        if len(socket_list) < len(list_of_names):
            raise SyntaxError("\033[91m Too many values to unpack.\033[0m")
        elif len(socket_list) > len(list_of_names):
            raise SyntaxError("\033[91m Not enough values to unpack.\033[0m")

        for i in range(len(socket_list)):
            self.locals[list_of_names[i]] = socket_list[i]

    def visit_AugAssign(self, node):
        id_to_augment = node.target.id
        socket_to_augment  = self.get_socket_from_node(node.target)
        augmentation_value = self.get_socket_from_node(node.value)
        bopnode_type = node.op.__class__.__name__
        bop = self.create_bop(bopnode_type,socket_to_augment,augmentation_value)
        self.locals[id_to_augment] = bop.perform.out

        return [bop.perform.out]

    def visit_Return(self, node):
        returned_sckts = None
        if type(node.value) is ast.Tuple or type(node.value) is ast.List:
            returned_sckts = []
            for elt in node.value.elts:
                returned_sckts.append(self.get_socket_from_node(elt))
            if type(node.value) is ast.Tuple:
                returned_sckts = tuple(returned_sckts)
            self.returned_sckts = returned_sckts
        else:
            self.returned_sckts = self.get_socket_from_node(node.value)

    def unbind_tasks(self):
        if self.sequence:
            for lt in self.sequence.get_get_tasks_per_types():
                for t in lt:
                    for s in t.sockets:
                        s.reset()
        else:
            for bind in self.binding:
                if type(bind[0]) is builtins.core.Socket:
                    t = bind[0].task
                    for s in t.outputs:
                        try:
                            s.reset()
                        except:
                            pass
                    for s in t.inputs:
                        if s.has_data():
                            s.reset()

                if type(bind[1]) is builtins.core.Socket:
                    t = bind[1].task
                    for s in t.outputs:
                        try:
                            s.reset()
                        except:
                            pass
                    for s in t.inputs:
                        if s.has_data():
                            s.reset()

    def cast_to_socket(self, var, n_elmts=0, n_frames=1):
        if issubclass(type(var),np.number):
            sck_var_name = "cst_" + str(var) + "_" + type(var).__name__
        else:
            sck_var_name = "var_" + str(id(var))

        var_ = None
        if sck_var_name in self.local_modules:
            var_ = self.local_modules[sck_var_name].get.X
        elif type(var) is np.ndarray:
            array_pyaf = builtins.Array(var)
            array_pyaf.n_frames = n_frames
            self.local_modules[sck_var_name] = array_pyaf
            var_ = array_pyaf.get.X
        elif issubclass(type(var),np.number):
            array_pyaf = builtins.Array(var, n_elmts)
            self.local_modules[sck_var_name] = array_pyaf
            var_ = array_pyaf.get.X
        return var_

    def apply_binding(self):
        self.unbind_tasks()
        for b in self.binding:
            if type(b[0]) is not builtins.core.Socket:
                n_frames = b[1].task.module.n_frames
                n_elmts = b[1].n_elmts//n_frames
                new_name = ''
                if issubclass(type(b[0]),np.number):
                    new_name = "(" + type(b[1].dtype(b[0])).__name__ + ") " + str(b[0])
                b[0] = self.cast_to_socket(b[1].dtype(b[0]), n_elmts=n_elmts, n_frames=n_frames)
                if new_name: # If it is a constant, rename the node
                    b[0].task.module.name = new_name

        not_firsts = []
        for b in self.binding:
            if type(b[1]) is builtins.core.Task:
                if b[1] not in not_firsts:
                    not_firsts.append(b[1])

        for b in self.binding:
            if type(b[0]) is builtins.core.Socket:
                t = b[0].task
                if not t.inputs and not t in self.firsts and not t in not_firsts:
                    self.firsts.append(t)

        #for i in range(1,len(self.firsts)):
        #    self.binding.append([self.firsts[0]["status"], self.firsts[i]])

        for b in self.binding:
            if type(b[1]) is builtins.core.Socket or type(b[1]) is builtins.core.Task:
                b[1].bind(b[0])

    def create_sequence(self):
        self.sequence = builtins.core.Sequence(self.firsts, n_threads = self.n_threads)

    def reset(self):
        self.binding = []
        self.locals = self.init_locals.copy()
        self.local_modules = {}
        self.loop_firsts = []
        self.firsts = []
        self.returned_sckts = None
        self.sequence = None

    def create_binding(self):
        func_lines = inspect.getsource(self.func).splitlines(keepends=True)
        l = func_lines[1].find("def")
        func_src = ""
        for fl in func_lines[1:]:
            func_src += fl[l:]

        func_ast = ast.parse(func_src, mode='exec')

        self.visit(func_ast)

    def __call__(self, *args, **kwargs):
        has_changed = self.set_func_args(args, kwargs)
        if has_changed:
            self.sequence = None
        if self.sequence:
            if self.auto_loop:

                if self.debug and self.n_threads != 1:
                    self.n_threads = 1
                    self.create_sequence()

                for lt in self.sequence.get_tasks_per_types():
                    for t in lt:
                        t.debug = self.debug
                        if self.debug_limit > -1:
                            t.set_debug_limit(self.debug_limit)
                        t.stats = self.stats

                self.sequence.exec()
                return self.returned_sckts

            else:
                if self.n_threads != 1:
                    self.n_threads = 1
                    self.create_sequence()

                for lt in self.sequence.get_tasks_per_types():
                    for t in lt:
                        t.debug = self.debug
                        if self.debug_limit > -1:
                            t.set_debug_limit(self.debug_limit)
                        t.stats = self.stats

                while self.sequence.exec_step():
                    pass
                return self.returned_sckts
        else:
            self.reset          ()
            self.create_binding ()
            self.apply_binding  ()
            self.create_sequence()

            return self.__call__(*args, **kwargs)

    def print_stats(self):
        if hasattr(self, "sequence"):
            self.sequence.show_stats()

def jit(auto_loop=False, n_threads=1, debug=False, debug_limit=-1, stats = False):
    def inner(func):
        visitor = Visitor(func,
                          auto_loop   = auto_loop,
                          n_threads   = n_threads,
                          debug       = debug,
                          debug_limit = debug_limit,
                          stats       = stats)

        def wrapper(*args, **kwargs):
            return visitor(*args, **kwargs)

        wrapper.__visitor__ = visitor
        return wrapper
    return inner

__all__ = ["jit"]