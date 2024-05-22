#include "wrapper/Tools/Interface/Interface_clone.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_interface_clone(py::module_& scope)
{
	auto itf_class = py::class_<spu::tools::Interface_clone,
	                            pyaf::wrapper::py_Interface_clone,
								std::unique_ptr<spu::tools::Interface_clone, py::nodelete>
								>(scope, "Interface_clone");
	itf_class.def("clone", &spu::tools::Interface_clone::clone);
}