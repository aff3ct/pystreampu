#include "wrapper/Module/Probe/Occurrence/Probe_occurrence.hpp"

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_probe_occurrence(py::handle scope)
{
	py::class_<spu::module::Probe_occurrence, spu::module::Probe<uint8_t>>(scope, "Probe_occurrence")
		.def(py::init<const std::string &, spu::tools::Reporter_probe*>(), "col_name"_a, "reporter"_a = nullptr, py::keep_alive<1, 3>(), py::return_value_policy::take_ownership);
}