#include "wrapper/Module/Probe/Timestamp/Probe_timestamp.hpp"

namespace py = pybind11;
using namespace py::literals;

void
pyspu::wrapper::wrap_probe_timestamp(py::handle scope)
{
    py::class_<spu::module::Probe_timestamp, spu::module::Probe<uint8_t>>(scope, "Probe_timestamp")
      .def(py::init<const uint64_t, const std::string&, spu::tools::Reporter_probe*>(),
           "mod"_a,
           "col_name"_a,
           "reporter"_a = nullptr,
           py::keep_alive<1, 4>(),
           py::return_value_policy::take_ownership)
      .def(py::init<const std::string&, spu::tools::Reporter_probe*>(),
           "col_name"_a,
           "reporter"_a = nullptr,
           py::keep_alive<1, 4>(),
           py::return_value_policy::take_ownership);
}