#include "wrapper/Tools/Reporter/Reporter.hpp"
#include "wrapper/Tools/Reporter/Probe/Reporter_probe.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_reporter(py::module_& scope)
{
    auto rep_class =
      py::class_<spu::tools::Reporter, spu::tools::Interface_reset, pyspu::wrapper::py_Reporter>(scope, "Reporter");
    rep_class.def("init", &spu::tools::Reporter::init);
    rep_class.def_property_readonly("groups", &spu::tools::Reporter::get_groups);

    pyspu::wrapper::wrap_reporter_probe(scope);
}