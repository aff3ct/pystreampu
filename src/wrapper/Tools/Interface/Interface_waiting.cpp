#include "wrapper/Tools/Interface/Interface_waiting.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_interface_waiting(py::module_& scope)
{
	auto itf_class = py::class_<spu::tools::Interface_waiting,
								spu::tools::Interface_reset,
	                            pyaf::wrapper::py_Interface_waiting
								>(scope, "Interface_waiting");

	itf_class.def("send_cancel_signal", &spu::tools::Interface_waiting::send_cancel_signal);
	itf_class.def("wake_up", &spu::tools::Interface_waiting::wake_up);
	itf_class.def("cancel_waiting", &spu::tools::Interface_waiting::cancel_waiting);
}