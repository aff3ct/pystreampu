#include "wrapper/Module/Stateless/Stateless.hpp"

#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include "wrapper/Common/Tools/type_functions.h"

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_stateless(py::handle scope)
{
	auto stateless_class = py::class_<spu::module::Stateless, spu::module::Module>(scope, "Stateless",
	R"pbdoc(
    Stateless modules are modules that can be cloned automatically.
    )pbdoc"
	);
	stateless_class.def(py::init<>(), "Build a Stateless module", py::return_value_policy::take_ownership);
	stateless_class.def_property("name", &spu::module::Stateless::get_name,
	                                     &spu::module::Stateless::set_name);
}
