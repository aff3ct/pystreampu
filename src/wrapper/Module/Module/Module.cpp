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
  py::class_<Module, aff3ct::tools::Interface_clone, aff3ct::tools::Interface_get_set_n_frames>(scope, "Module",py::dynamic_attr())
{
}

void Wrapper_Module
::definitions()
{
	this->def(py::init<>(), py::return_value_policy::reference);
	this->def_property_readonly("tasks", [](Module& self) -> std::vector<std::shared_ptr<aff3ct::runtime::Task>> { return self.tasks; });
	this->def_property("name", [](const Module & m){return m.get_custom_name()==""?m.get_name():m.get_custom_name();}, &Module::set_custom_name);
	this->def("create_reset_task", &Module::create_reset_task);


	this->def("__getitem__",  [](Module& m, const std::string& s)
	{
		size_t pos = s.find("::", 0);
		if ((int)pos < 0)
			return py::cast(&m(s));
		else
			return py::cast(&m[s]);
	}, py::keep_alive<0,1>());

	/*this->def("__setitem__", [](Module& m, const std::string& s, aff3ct::runtime::Socket& sck){
		size_t pos = s.find("::", 0);
		if ((int)pos < 0)
			m(s) = sck;
		else
			m[s] = sck;
	});
	this->def("__setitem__", [](Module& m, const std::string& s, py::array& arr){
		size_t pos = s.find("::", 0);

		if ((int)pos >= 0)
		{
			py::object py_sck = py::cast(&(m[s]));
			py_sck.attr("bind")(arr);
		}
		else
		{
			std::stringstream message;
			message << "Cannot bind an array to a task.";
			throw std::runtime_error(message.str());
		}

	});

	this->def("__getattr__", [](Module& m, const std::string& attr){
    try
    {
            return py::cast(&m(attr));
    }
    catch(const aff3ct::tools::invalid_argument& e)
    {
        py::object py_m = py::cast(m);
        const std::string class_str = py_m.attr("__class__").attr("__name__").cast<std::string>();
        const std::string str = "'" + class_str + "' object has no attribute '" + attr + "'";
        throw py::attribute_error(str);
    }
	},"If 'attr' is a task name, module.attr returns the corresponding task. If 'attr' is not task name it returns the classical module.attr.", "attr"_a, py::keep_alive<0,1>());

	this->def("__dir__", [](const Module& m){
		py::list ret = py::module::import("builtins").attr("object").attr("__dir__")(py::cast(m));
		for (auto & t : m.tasks)
			ret.append(py::cast(t->get_name()));
		return ret;
	});
*/
};
