#include <functional>
#include <iostream>
#include <sstream>

#include "wrapper/Module/Module/Module.hpp"

#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Runtime/Task/Task.hpp"



namespace py = pybind11;
using namespace py::literals;
using namespace spu::module;
using namespace pyspu::wrapper;
using namespace spu::runtime;

void pyspu::wrapper::wrap_module(py::handle scope)
{
auto py_module_class = py::class_<Module, spu::tools::Interface_clone, spu::tools::Interface_get_set_n_frames>(
      scope,
      "Module",
      py::dynamic_attr());

    //py_module_class.def(py::init<>());
    //py_module_class.def(py::init<const Module&>());

    py_module_class.def_property_readonly(
      "tasks",
      [](Module& self)
      {
          std::vector<spu::runtime::Task*> tasks;
          for (auto t : self.tasks)
              tasks.push_back(t.get());
          return tasks;
      },
      R"pbdoc(Module's list of tasks.)pbdoc");

    py_module_class.def_property(
      "name",
      [](const Module& m) { return m.get_custom_name() == "" ? m.get_name() : m.get_custom_name(); },
      &Module::set_custom_name,
      R"pbdoc(Name of the module)pbdoc");

    py_module_class.def(
      "__getitem__",
      [](Module& m, const std::string& key)
      {
          size_t pos = key.find("::", 0);
          if ((int)pos < 0)
              return py::cast(&m(key));
          else
              return py::cast(&m[key]);
      },
      "key"_a,
      py::keep_alive<0, 1>(),
      R"pbdoc(
        Return the task or the socket corresponding to the key.

        Args:
            key (str): key representing a task or a socket.
              If key is of the form "task_name" then the task with the name
              "task_name" is returned.
              If key is of the form "task_name::socket_name" then the socket
              with the name "socket_name" of the task named "task_name"
              is returned.

        Returns:
            Task | Socket : task or socket described by the key.
    )pbdoc",
      py::is_operator());
};
