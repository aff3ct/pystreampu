#include "wrapper/Module/Probe/Occurrence/Probe_occurrence.hpp"

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_probe_occurrence(py::handle scope)
{
	py::class_<aff3ct::module::Probe_occurrence, aff3ct::module::Probe<uint8_t>>(scope, "Probe_occurrence")
		.def(py::init<const std::string &, aff3ct::tools::Reporter_probe&, const int>(), "col_name"_a, "reporter"_a, "n_frames"_a=1, py::return_value_policy::take_ownership);
}