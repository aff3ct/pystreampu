#include "wrapper/Module/Probe/Probe.hpp"

#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"

#include "wrapper/Module/Probe/Latency/Probe_latency.hpp"
#include "wrapper/Module/Probe/Occurrence/Probe_occurrence.hpp"
#include "wrapper/Module/Probe/Throughput/Probe_throughput.hpp"
#include "wrapper/Module/Probe/Time/Probe_time.hpp"
#include "wrapper/Module/Probe/Timestamp/Probe_timestamp.hpp"

namespace py = pybind11;
using namespace py::literals;

void
pyaf::wrapper::wrap_probe(py::handle scope)
{
    // AProbe has a protected destructor
    auto aprobe_class = py::class_<spu::module::AProbe,
                                   spu::module::Module,
                                   spu::tools::Interface_reset,
                                   std::unique_ptr<spu::module::AProbe, py::nodelete>>(scope, "AProbe");

    using lT = tl::type_list<ALL_DTYPES>;
    lT::for_each(
      [&](auto t)
      {
          using T = typename decltype(t)::type;
          std::string T_str = spu::runtime::type_to_string[typeid(T)];
          auto probe_class = py::class_<spu::module::Probe<T>, spu::module::AProbe, pyaf::wrapper::py_Probe<T>>(
            scope, std::string("Probe_" + T_str).c_str());
          // probe_class.def(py::init<const int, const std::string &>(), "size"_a,
          // "col_name"_a, py::return_value_policy::take_ownership);
          probe_class.def("set_col_unit", &spu::module::Probe<T>::set_col_unit);
          probe_class.def("set_col_buff_size", &spu::module::Probe<T>::set_col_buff_size);
          probe_class.def("set_col_fmtflags", &spu::module::Probe<T>::set_col_fmtflags);
          probe_class.def("set_col_prec", &spu::module::Probe<T>::set_col_prec);
          probe_class.def("set_col_size", &spu::module::Probe<T>::set_col_size);
          probe_class.def("register_reporter", &spu::module::Probe<T>::register_reporter, py::keep_alive<1, 2>());
          probe_class.def("get_col_name", &spu::module::Probe<T>::get_col_name);

          py::class_<spu::module::Probe_value<T>, spu::module::Probe<T>>(scope,
                                                                         std::string("Probe_value_" + T_str).c_str())
            .def(py::init<const int, const std::string&, spu::tools::Reporter_probe*>(),
                 "size"_a,
                 "col_name"_a,
                 "reporter"_a,
                 py::keep_alive<1, 2>(),
                 py::return_value_policy::take_ownership);
      });

    pyaf::wrapper::wrap_probe_latency(scope);
    pyaf::wrapper::wrap_probe_occurrence(scope);
    pyaf::wrapper::wrap_probe_throughput(scope);
    pyaf::wrapper::wrap_probe_time(scope);
    pyaf::wrapper::wrap_probe_timestamp(scope);
}
