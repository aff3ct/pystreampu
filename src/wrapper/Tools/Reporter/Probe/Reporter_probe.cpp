#include "wrapper/Tools/Reporter/Probe/Reporter_probe.hpp"
#include "wrapper/Common/Tools/Format/Format.hpp"

#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_reporter_probe(py::module_ &scope) {
  auto rep_probe_class =
      py::class_<spu::tools::Reporter_probe, spu::tools::Reporter,
                 spu::tools::Interface_get_set_n_frames>(scope,
                                                         "Reporter_probe");

  // Constructor
  rep_probe_class.def(py::init<const std::string &, const std::string &>(),
                      "group_name"_a, "group_description"_a);
  rep_probe_class.def("register_probes", &spu::tools::Reporter_probe::register_probes);
}
