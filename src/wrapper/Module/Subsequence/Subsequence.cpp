#include "wrapper/Module/Subsequence/Subsequence.hpp"

#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include "wrapper/Common/Tools/type_functions.h"

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_subsequence(py::handle scope)
{
	auto subsequence_class = py::class_<aff3ct::module::Subsequence, aff3ct::module::Module>(scope, "Subsequence");
	subsequence_class.def(py::init<aff3ct::runtime::Sequence &>(), "sequence"_a, py::keep_alive<1, 2>());
	subsequence_class.def_property_readonly("sequence", &aff3ct::module::Subsequence::get_sequence);
}
