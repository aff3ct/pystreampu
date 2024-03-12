#include "wrapper/Module/Probe/Timestamp/Probe_timestamp.hpp"

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_probe_timestamp(py::handle scope)
{
	py::class_<aff3ct::module::Probe_timestamp, aff3ct::module::Probe<uint8_t>>(scope, "Probe_timestamp")
		.def(py::init<const std::string &, const uint64_t, aff3ct::tools::Reporter_probe&, const int>(), "col_name"_a, "mod"_a, "reporter"_a, "n_frames"_a=1, py::return_value_policy::take_ownership)
		.def(py::init<const std::string &, aff3ct::tools::Reporter_probe&, const int>(), "col_name"_a, "reporter"_a, "n_frames"_a=1, py::return_value_policy::take_ownership);
}
