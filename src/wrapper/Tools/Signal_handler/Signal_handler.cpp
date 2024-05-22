#include "wrapper/Tools/Signal_handler/Signal_handler.hpp"

#include "wrapper/Common/pystreambuf.h"
#include <pybind11/chrono.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_signal_handler(py::module_ &scope) {
  auto signal_handler_class =
      py::class_<spu::tools::Signal_handler>(scope, "Signal_handler");
  signal_handler_class.def(py::init<>());
  signal_handler_class.def_property_readonly_static(
      "sigint", &spu::tools::Signal_handler::is_sigint);
  signal_handler_class.def_property_readonly_static(
      "sigsegv", &spu::tools::Signal_handler::is_sigsegv);
  signal_handler_class.def_static("init", &spu::tools::Signal_handler::init);
  signal_handler_class.def_static("reset_sigint",
                                  &spu::tools::Signal_handler::reset_sigint);
  signal_handler_class.def_static("reset_sigsegv",
                                  &spu::tools::Signal_handler::reset_sigsegv);
}