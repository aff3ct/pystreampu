=================
AFF3CT Python API
=================

.. automodule:: aff3ct
.. currentmodule:: aff3ct

Key concepts
------------

AFF3CT is built around the key concepts called :Module:, :Task:, :Socket:, Sequence, and Pipeline.
In the AFF3CT Python API, a :class: corresponds to each concept.

.. autosummary::
    :toctree: _autosummary
    :nosignatures:

    Module
    Task
    Socket


Write custom modules in Python
------------------------------

Stateless modules
Statefull modules

.. code-block:: python
    :linenos:

    # Create a stateless module
    min10 = aff3ct.Stateless()
    # Set module name
    min10.name = "Minimum10"
    # create a task for the 'min32' module
    tsk = min10.create_task("find_min")
    # create in/out sockets for the task
    min10.create_socket_in (tsk, "in", 10, aff3ct.int32)
    min10.create_socket_out(tsk, "out", 1, aff3ct.int32)
    # define the code to execute when the
    # 'find_min' task is called
    def find_min_impl(mdl, tsk, frm_id):
        x = tsk["in"].numpy
        y = tsk["out"].numpy
        y[0] = x[0]
        for i in range(1,len(x)):
            y[0] = min(y[0], x[i])
        return aff3ct.Task.status.SUCCESS
    # Associate the code to 'find_min'
    min10.create_codelet(tsk, find_min_impl)

Use the newly created module

.. code-block:: python

    import numpy as np
    x = aff3ct.int32([96, 48, 18, 99, 23, 71, 46, 39, 73, 47])
    y = min10.find_min(x)
    y

Should return

.. code-block:: bash

    socket([18], dtype=int32, name=out, task=Minimum10.find_min)

Help
----

.. autosummary::
    :toctree: _autosummary
    :nosignatures:

    help

.. _data-generation:

Simple data generation
----------------------

.. autosummary::
    :toctree: _autosummary
    :nosignatures:

    arange
    array
    ones
    zeros

.. _binary-ops:

Binary operators
----------------

.. autosummary::
    :toctree: _autosummary
    :nosignatures:

    add
    bitwise_and
    bitwise_not
    bitwise_or
    bitwise_xor
    bop
    div
    equal
    greater
    greater_equal
    less
    less_equal
    mul
    not_equal
    max
    min
    sub

.. _unary-ops:

Unary operators
---------------

.. autosummary::
    :toctree: _autosummary
    :nosignatures:

    abs
    cast
    neg
    uop

Data Types
----------

.. autosummary::
    :toctree: _autosummary
    :nosignatures:

    dtype