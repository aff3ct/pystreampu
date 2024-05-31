#include "wrapper/Module/Probe/Latency/Probe_latency.hpp"

namespace py = pybind11;
using namespace py::literals;

void
pyspu::wrapper::wrap_probe_latency(py::handle scope)
{
    py::class_<spu::module::Probe_latency, spu::module::Probe<uint8_t>>(scope, "Probe_latency")
      .def(py::init<const std::string&, spu::tools::Reporter_probe*>(),
           "col_name"_a,
           "reporter"_a = nullptr,
           py::keep_alive<1, 3>(),
           py::return_value_policy::take_ownership);
}