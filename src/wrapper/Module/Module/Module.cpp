#include <pybind11/functional.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <functional>
#include <iostream>
#include <sstream>

#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Module/Module/Module.hpp"
#include "wrapper/Runtime/Task/Task.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace spu::module;
using namespace pyaf::wrapper;
using namespace spu::runtime;

Wrapper_Module ::Wrapper_Module(py::handle scope)
    : Wrapper_py(),
      py::class_<Module, Module_Publicist, spu::tools::Interface_clone,
                 spu::tools::Interface_get_set_n_frames>(scope, "Module",
                                                         py::dynamic_attr()) {}

void Wrapper_Module ::definitions() {
  this->def(py::init<>());
  this->def(py::init<const Module &>());
  this->def_property("n_frames_per_wave", &Module::get_n_frames_per_wave,
                     &Module_Publicist::set_n_frames_per_wave);

  this->def_property_readonly(
      "tasks",
      [](Module &self) {
        std::vector<spu::runtime::Task *> tasks;
        for (auto t : self.tasks)
          tasks.push_back(t.get());
        return tasks;
      },
      R"pbdoc(Module's list of tasks.)pbdoc");

  this->def_property(
      "name",
      [](const Module &m) {
        return m.get_custom_name() == "" ? m.get_name() : m.get_custom_name();
      },
      &Module::set_custom_name, R"pbdoc(Name of the module)pbdoc");

  this->def(
      "create_socket_in",
      [](Module_Publicist &mdl, spu::runtime::Task &task,
         const std::string &name, const size_t n_elmts,
         const pyaf::dtype dtype) {
        return mdl.create_socket_in(task, name, n_elmts,
                                    utils::str2typeid(dtype.get_name()));
      },
      "task"_a, "name"_a, "n_elmts"_a, "dtype"_a,
      R"pbdoc(
        Create a new input socket to a task.
    )pbdoc");

  this->def(
      "create_socket_out",
      [](Module_Publicist &mdl, spu::runtime::Task &task,
         const std::string &name, const size_t n_elmts,
         const pyaf::dtype dtype) {
        return mdl.create_socket_out(task, name, n_elmts,
                                     utils::str2typeid(dtype.get_name()));
      },
      "task"_a, "name"_a, "n_elmts"_a, "dtype"_a,
      R"pbdoc(
        Create a new output socket to a task.
    )pbdoc");

  this->def(
      "create_socket_fwd",
      [](Module_Publicist &mdl, spu::runtime::Task &task,
         const std::string &name, const size_t n_elmts,
         const pyaf::dtype dtype) {
        return mdl.create_socket_fwd(task, name, n_elmts,
                                     utils::str2typeid(dtype.get_name()));
      },
      "task"_a, "name"_a, "n_elmts"_a, "dtype"_a,
      R"pbdoc(
        Create a new forward socket to a task.
    )pbdoc");

  this->def(
      "create_task",
      [](Module_Publicist &mdl, const std::string &name) {
        return &mdl.create_task(name);
      },
      "name"_a,
      R"pbdoc(
        Create a new task.

        Args:
            name (str): name of the task

        Returns:
            Task: newly created task.

    )pbdoc");

  this->def("create_codelet", &Module_Publicist::create_codelet);

  this->def(
      "__getitem__",
      [](Module &m, const std::string &key) {
        size_t pos = key.find("::", 0);
        if ((int)pos < 0)
          return py::cast(&m(key));
        else
          return py::cast(&m[key]);
      },
      "key"_a, py::keep_alive<0, 1>(),
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

  def("deep_copy", &Module_Publicist::deep_copy);
};
