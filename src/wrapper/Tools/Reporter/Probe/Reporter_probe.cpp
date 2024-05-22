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

  // Probe factory
  using lT = tl::type_list<ALL_DTYPES>;
  lT::for_each([&](auto t) {
    using T = typename decltype(t)::type;
    std::string T_str = spu::runtime::type_to_string[typeid(T)];
    // rep_probe_class.def(std::string("_create_probe_value_" + T_str).c_str(),
    // &spu::tools::Reporter_probe::create_probe_value<T>, "name"_a, "unit"_a =
    // "", "buffer_size"_a = 100, "socket_size"_a = 1, "format"_a =
    // pyaf::fmtflags::scientific, "precision"_a = 3);
  });
}
