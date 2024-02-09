#include "wrapper/Tools/Interface/Interface_reset.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_interface_reset(py::module_& scope)
{
	auto itf_class = py::class_<aff3ct::tools::Interface_reset,
	                            pyaf::wrapper::py_Interface_reset,
								std::unique_ptr<aff3ct::tools::Interface_reset, py::nodelete>
								>(scope, "Interface_reset");
	itf_class.def("reset", &aff3ct::tools::Interface_reset::reset);
}