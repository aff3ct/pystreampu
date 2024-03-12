#include "wrapper/Tools/Interface/Interface_waiting.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_interface_waiting(py::module_& scope)
{
	auto itf_class = py::class_<aff3ct::tools::Interface_waiting,
								aff3ct::tools::Interface_reset,
	                            pyaf::wrapper::py_Interface_waiting
								>(scope, "Interface_waiting");

	itf_class.def("send_cancel_signal", &aff3ct::tools::Interface_waiting::send_cancel_signal);
	itf_class.def("wake_up", &aff3ct::tools::Interface_waiting::wake_up);
	itf_class.def("cancel_waiting", &aff3ct::tools::Interface_waiting::cancel_waiting);
}