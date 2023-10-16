from .. import builtins

from graphviz import Digraph
import json
import os

def get_style(d):
    style = ""
    for k,v in d.items():
        style += k + ' = "' + v + '" '
    return style

def replace_html_special_chars(str):
    str = str.replace('&','&#38;')
    str = str.replace('(','&#40;')
    str = str.replace(')','&#41;')
    str = str.replace('*','&#42;')
    str = str.replace('+','&#43;')
    str = str.replace('-','&#45;')
    str = str.replace('/','&#47;')
    str = str.replace('<','&#60;')
    str = str.replace('=','&#61;')
    str = str.replace('>','&#62;')
    str = str.replace('|','&#124;')
    return str

def task_dot(task, style):

    stateless_task_style           = get_style(style["stateless.task"]["task"          ])
    stateless_task_name_style      = get_style(style["stateless.task"]["task.name"     ])
    stateless_socket_input_style   = get_style(style["stateless.task"]["socket.input"  ])
    stateless_socket_output_style  = get_style(style["stateless.task"]["socket.output" ])
    stateless_socket_forward_style = get_style(style["stateless.task"]["socket.forward"])
    stateless_socket_empty_style   = get_style(style["stateless.task"]["socket.empty"  ])
    label = '<<table {stateless_task_style}>{lines}</table>>'
    s_out = []
    s_in  = []
    s_fwd = []
    for s in task.sockets:
        if s.direction == builtins.core.Socket.directions.IN:
            s_in.append(s)
        elif s.direction == builtins.core.Socket.directions.OUT:
            s_out.append(s)
        elif s.direction == builtins.core.Socket.directions.FWD:
            s_in.append(s)
            s_out.append(s)
        else:
            # TODO : Error message
            return NotImplemented
    n_in = len(s_in)
    n_out = len(s_out)

    n_lines = max(n_in,n_out)
    module_name = replace_html_special_chars(task.module.name)
    task_name   = replace_html_special_chars(task.name)
    node_name =  module_name + "<br/>" + task_name
    lines     ='\n<tr>{in_sck_name_0}<td rowspan="{n_lines}" {stateless_task_name_style} port="fake">{node_name}</td>{out_sck_name_0}</tr>\n'
    for l in range(1,n_lines):
        lines += '<tr>{in_sck_name_' + str(l) + '}{out_sck_name_'+ str(l) +'}</tr>\n'

    for l in range(n_lines):
        if l < n_in:
            socket_style = 'stateless_socket_input_style'
            if s_in[l].direction == builtins.core.Socket.directions.FWD:
                socket_style = 'stateless_socket_forward_style'

            lines = lines.replace('{in_sck_name_' + str(l) + '}','<td {'+ socket_style +'} port="' + s_in[l].name + '_in">' + s_in[l].name+'</td>')
        elif n_in > 0:
            lines = lines.replace('{in_sck_name_' + str(l) + '}','<td {stateless_socket_empty_style}></td>')
        else:
            lines = lines.replace('{in_sck_name_' + str(l) + '}','')
        if l < n_out:
            socket_style = 'stateless_socket_output_style'
            if s_out[l].direction == builtins.core.Socket.directions.FWD:
                socket_style = 'stateless_socket_forward_style'

            lines = lines.replace('{out_sck_name_' + str(l) + '}','<td {'+ socket_style +'} port="' + s_out[l].name + '_out">' + s_out[l].name+'</td>')
        else:
            lines = lines.replace('{out_sck_name_' + str(l) + '}','<td {stateless_socket_empty_style}></td>')
    lines = lines.format(n_lines                        = n_lines,
                         node_name                      = node_name,
                         stateless_task_name_style      = stateless_task_name_style,
                         stateless_socket_input_style   = stateless_socket_input_style,
                         stateless_socket_output_style  = stateless_socket_output_style,
                         stateless_socket_forward_style = stateless_socket_forward_style,
                         stateless_socket_empty_style   = stateless_socket_empty_style
                         )
    label = label.format(lines=lines, stateless_task_style=stateless_task_style)

    return label

def viz(seq, display_data = False, style_json = os.path.join(os.path.dirname(__file__),"style.json")):
    tasks = []
    for lt in seq.get_tasks_per_types():
        for t in lt:
            #if t not in tasks:
            tasks.append(t)
    binding = []
    for t in tasks:
        for s_out in t.outputs + t.forwards:
            l_s_in = s_out.bound_sockets

            for s_in in l_s_in:
                if s_in.task in tasks:
                    binding.append([s_out, s_in])

    inputs_id = [id(b[1]) for b in binding]
    for t in tasks:
        for s_in in t.inputs + t.forwards:
            if id(s_in) not in inputs_id:
                if s_in.has_data():
                    binding.append([s_in.dataaddr, s_in])

    return viz_(binding, display_data, style_json)

def viz_(binding, display_data = False, style_json = os.path.join(os.path.dirname(__file__),"style.json")):
    tasks = []
    consts = []
    const_names = []
    n_consts = 0
    for b in binding:
        if type(b[0]) is builtins.core.Socket:
            t = b[0].task
            if t not in tasks:
                tasks.append(t)
        else:
            if b[0] not in consts:
                consts.append(b[0])
                const_names.append("c_" + str(n_consts))
                n_consts += 1
        if type(b[1]) is builtins.core.Socket:
            t = b[1].task
            if t not in tasks:
                tasks.append(t)
        elif type(b[1]) is builtins.core.Task:
            if b[1] not in tasks:
                tasks.append(b[1])
        else:
            if b[1] not in consts:
                consts.append(b[1])
                const_names.append("c_" + str(n_consts))
                n_consts += 1

    with open(style_json, 'r') as f:
        style = json.load(f)

    dot = Digraph()
    dot.node_attr['shape'] = 'none'
    dot.graph_attr['rankdir'] = 'LR'
    dot.graph_attr['splines']='curved'
    binding_fwd = []
    for it in range(len(tasks)):
        t = tasks[it]
        for fwd_sck in t.forwards:
            binding_fwd.append([fwd_sck, fwd_sck])

        dot.node(name='tsk'+str(it),label = task_dot(t,style))
        for out_sck in t.outputs:
            if not out_sck.bound_sockets and not out_sck.name == 'status' :
                nde_name = 'output_' + str(out_sck.dataaddr)
                dot.node(name=nde_name, label = '')
                binding.append([out_sck, nde_name])

    for it in range(len(consts)):
        dot.node(name='c_'+str(it),label = "c_"+str(it), **style["const"])

    for b in binding_fwd:
        s_out_idx =  tasks.index(b[0].task)
        out_name = 'tsk'+str(s_out_idx)+":"+b[0].name + "_out:w"

        s_in_idx  =  tasks.index(b[1].task)
        in_name = 'tsk'+str(s_in_idx)+":"+b[1].name + "_in:e"

        dot.edge(in_name, out_name, constraint="false", spline="curved")

    for b in binding:
        if type(b[0]) is builtins.core.Socket:
            s_out_idx =  tasks.index(b[0].task)
            out_name = 'tsk'+str(s_out_idx)+":"+b[0].name + "_out"
        else:
            s_out_idx =  consts.index(b[0])
            out_name = const_names[s_out_idx]

        if type(b[1]) is builtins.core.Socket:
            s_in_idx  =  tasks.index(b[1].task)
            in_name = 'tsk'+str(s_in_idx)+":"+b[1].name + "_in"
        elif type(b[1]) is builtins.core.Task:
            s_in_idx  =  tasks.index(b[1])
            in_name = 'tsk'+str(s_in_idx)+":fake"
        elif type(b[1]) is str:
            in_name = b[1]
        else:
            s_in_idx =  consts.index(b[1])
            in_name = const_names[s_in_idx]
        if display_data:
            dot.edge(out_name, in_name, label=str(b[0]))
        else:
            dot.edge(out_name, in_name)

    return dot

__all__ = ["viz"]