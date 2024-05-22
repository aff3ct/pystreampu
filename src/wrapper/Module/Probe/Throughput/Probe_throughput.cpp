#include "wrapper/Module/Probe/Throughput/Probe_throughput.hpp"

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_probe_throughput(py::handle scope) {
  py::class_<spu::module::Probe_throughput, spu::module::Probe<uint8_t>>(
      scope, "Probe_throughput")
      .def(py::init<const size_t, const std::string &,
                    spu::tools::Reporter_probe *>(),
           "data_size"_a, "col_name"_a, "reporter"_a = nullptr,
           py::keep_alive<1, 4>(), py::return_value_policy::take_ownership)
      .def(py::init<const size_t, const std::string &, const double,
                    spu::tools::Reporter_probe *>(),
           "data_size"_a, "col_name"_a, "factor"_a, "reporter"_a = nullptr,
           py::keep_alive<1, 5>(), py::return_value_policy::take_ownership);
}