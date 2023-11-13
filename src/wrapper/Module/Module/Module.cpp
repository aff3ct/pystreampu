#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>

#include <functional>
#include <iostream>
#include <sstream>

#include "wrapper/Module/Module/Module.hpp"
#include "wrapper/Runtime/Task/Task.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace aff3ct::module;
using namespace pyaf::wrapper;
using namespace aff3ct::runtime;

Wrapper_Module
::Wrapper_Module(py::handle scope)
: Wrapper_py(),
  py::class_<Module, Module_Publicist, aff3ct::tools::Interface_clone, aff3ct::tools::Interface_get_set_n_frames>(scope, "Module",py::dynamic_attr())
{
}

void Wrapper_Module
::definitions()
{
	this->def(py::init<>(), py::return_value_policy::reference);
	this->def_property_readonly("tasks", [](Module& self) -> std::vector<std::shared_ptr<aff3ct::runtime::Task>> { return self.tasks; },  R"pbdoc(Module's list of tasks.)pbdoc");
	this->def_property("doc", &Module::get_doc, &Module_Publicist::set_doc, R"pbdoc(Module's doc string)pbdoc");
	this->def_property("name", [](const Module & m){return m.get_custom_name()==""?m.get_name():m.get_custom_name();}, &Module::set_custom_name, R"pbdoc(Name of the module)pbdoc");
	//this->def("create_socket_in", &Module_Publicist::create_socket_in);
	//this->def("create_socket_out", &Module_Publicist::create_socket_out);
	this->def("create_task",
	[](Module_Publicist& mdl, const std::string &name, const std::string &doc)
	{
		return mdl.create_task(name, doc);
	},"name"_a, "doc"_a="",
	R"pbdoc(
        Create a new task.

        Args:
            name (str): name of the task
            doc (str): task doc string

        Returns:
            Task: newly created task.

    )pbdoc");
	this->def("create_codelet", &Module_Publicist::create_codelet);

	this->def("__getitem__",  [](Module& m, const std::string& key)
	{
		size_t pos = key.find("::", 0);
		if ((int)pos < 0)
			return py::cast(&m(key));
		else
			return py::cast(&m[key]);
	}, "key"_a, py::keep_alive<0,1>(),
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
    )pbdoc");

};
