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

    stateless_task_style          = get_style(style["stateless.task"]["task"         ])
    stateless_task_name_style     = get_style(style["stateless.task"]["task.name"    ])
    stateless_socket_input_style  = get_style(style["stateless.task"]["socket.input" ])
    stateless_socket_output_style = get_style(style["stateless.task"]["socket.output"])
    stateless_socket_empty_style  = get_style(style["stateless.task"]["socket.empty" ])

    label = '<<table {stateless_task_style}>{lines}</table>>'
    s_out = []
    s_in  = []
    for s in task.sockets:
        if s.direction == "in":
            s_in.append(s)
        else:
            s_out.append(s)
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
            lines = lines.replace('{in_sck_name_' + str(l) + '}','<td {stateless_socket_input_style} port="' + s_in[l].name + '">' + s_in[l].name+'</td>')
        elif n_in > 0:
            lines = lines.replace('{in_sck_name_' + str(l) + '}','<td {stateless_socket_empty_style}></td>')
        else:
            lines = lines.replace('{in_sck_name_' + str(l) + '}','')
        if l < n_out:
            lines = lines.replace('{out_sck_name_' + str(l) + '}','<td {stateless_socket_output_style} port="' + s_out[l].name + '">' + s_out[l].name+'</td>')
        else:
            lines = lines.replace('{out_sck_name_' + str(l) + '}','<td {stateless_socket_empty_style}></td>')
    lines = lines.format(n_lines                       = n_lines,
                         node_name                     = node_name,
                         stateless_task_name_style     = stateless_task_name_style,
                         stateless_socket_input_style  = stateless_socket_input_style,
                         stateless_socket_output_style = stateless_socket_output_style,
                         stateless_socket_empty_style  = stateless_socket_empty_style
                         )
    label = label.format(lines=lines, stateless_task_style=stateless_task_style)

    return label

def viz(seq, style_json = os.path.join(os.path.dirname(__file__),"style.json")):
    tasks = []
    for lt in seq.get_tasks_per_types():
        for t in lt:
            #if t not in tasks:
            tasks.append(t)
    binding = []
    for t in tasks:
        for s_out in t.outputs:
            l_s_in = s_out.bound_sockets
            for s_in in l_s_in:
                if s_in.task in tasks:
                    binding.append([s_out, s_in])

    inputs_id = [id(b[1]) for b in binding]
    for t in tasks:
        for s_in in t.inputs:
            if id(s_in) not in inputs_id:
                if s_in.has_data():
                    binding.append([s_in.dataaddr, s_in])

    return viz_(binding, style_json)

def viz_(binding, style_json = os.path.join(os.path.dirname(__file__),"style.json")):
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

    for it in range(len(tasks)):
        t = tasks[it]
        dot.node(name='tsk'+str(it),label = task_dot(t,style))

    for it in range(len(consts)):
        dot.node(name='c_'+str(it),label = "c_"+str(it), **style["const"])


    for b in binding:
        if type(b[0]) is builtins.core.Socket:
            s_out_idx =  tasks.index(b[0].task)
            out_name = 'tsk'+str(s_out_idx)+":"+b[0].name
        else:
            s_out_idx =  consts.index(b[0])
            out_name = const_names[s_out_idx]

        if type(b[1]) is builtins.core.Socket:
            s_in_idx  =  tasks.index(b[1].task)
            in_name = 'tsk'+str(s_in_idx)+":"+b[1].name
        elif type(b[1]) is builtins.core.Task:
            s_in_idx  =  tasks.index(b[1])
            in_name = 'tsk'+str(s_in_idx)+":fake"
        else:
            s_in_idx =  consts.index(b[1])
            in_name = const_names[s_in_idx]

        dot.edge(out_name, in_name)

    return dot

__all__ = ["viz"]