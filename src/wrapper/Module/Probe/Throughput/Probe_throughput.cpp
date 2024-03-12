#include "wrapper/Module/Probe/Throughput/Probe_throughput.hpp"

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_probe_throughput(py::handle scope)
{
	py::class_<aff3ct::module::Probe_throughput, aff3ct::module::Probe<uint8_t>>(scope, "Probe_throughput")
		.def(py::init<const size_t, const std::string &, aff3ct::tools::Reporter_probe&, const int>(), "data_size"_a, "col_name"_a, "reporter"_a, "n_frames"_a=1, py::return_value_policy::take_ownership)
		.def(py::init<const size_t, const std::string &, const double, aff3ct::tools::Reporter_probe&, const int>(), "data_size"_a, "col_name"_a, "factor"_a, "reporter"_a, "n_frames"_a=1, py::return_value_policy::take_ownership);
}