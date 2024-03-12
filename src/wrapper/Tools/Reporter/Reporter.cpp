#include "wrapper/Tools/Reporter/Reporter.hpp"
#include "wrapper/Tools/Reporter/Probe/Reporter_probe.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_reporter(py::module_& scope)
{
	auto rep_class = py::class_<aff3ct::tools::Reporter, aff3ct::tools::Interface_reset, pyaf::wrapper::py_Reporter>(scope, "Reporter");
    rep_class.def("init", &aff3ct::tools::Reporter::init);
    rep_class.def_property_readonly("groups", &aff3ct::tools::Reporter::get_groups);

	pyaf::wrapper::wrap_reporter_probe(scope);
}