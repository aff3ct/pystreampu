#include "wrapper/Tools/Interface/Interface_set_seed.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_interface_set_seed(py::module_& scope)
{
	auto itf_class = py::class_<aff3ct::tools::Interface_set_seed,
	                            pyaf::wrapper::py_Interface_set_seed,
								std::unique_ptr<aff3ct::tools::Interface_set_seed, py::nodelete>
								>(scope, "Interface_set_seed");

	itf_class.def("set_seed", &aff3ct::tools::Interface_set_seed::set_seed);
}