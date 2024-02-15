#include "wrapper/Tools/Interface/Interface_is_done.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_interface_is_done(py::module_& scope)
{
	auto itf_class = py::class_<aff3ct::tools::Interface_is_done,
	                            pyaf::wrapper::py_Interface_is_done,
								std::unique_ptr<aff3ct::tools::Interface_is_done, py::nodelete>
								>(scope, "Interface_is_done");
	itf_class.def("is_done", &aff3ct::tools::Interface_is_done::is_done);
}