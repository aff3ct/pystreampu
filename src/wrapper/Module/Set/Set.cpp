#include "wrapper/Module/Set/Set.hpp"

#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include "wrapper/Common/Tools/type_functions.h"

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_set(py::handle scope)
{
	auto set_class = py::class_<spu::module::Set, spu::module::Module>(scope, "Set");
	set_class.def(py::init<spu::runtime::Sequence &>(), "sequence"_a, py::keep_alive<1, 2>());
	set_class.def_property_readonly("sequence", &spu::module::Set::get_sequence);
}
