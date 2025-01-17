#include "wrapper/Tools/Signal_handler/Signal_handler.hpp"

#include "wrapper/Common/pybind11_common.h"

namespace py = pybind11;
using namespace py::literals;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_signal_handler(py::module_& scope)
{
    auto signal_handler_class = py::class_<spu::tools::Signal_handler>(scope, "Signal_handler");
    signal_handler_class.def_static("is_sigint", &spu::tools::Signal_handler::is_sigint);
    signal_handler_class.def_static("is_sigsegv", &spu::tools::Signal_handler::is_sigsegv);
    signal_handler_class.def_static("init", &spu::tools::Signal_handler::init);
    signal_handler_class.def_static("reset_sigint", &spu::tools::Signal_handler::reset_sigint);
    signal_handler_class.def_static("reset_sigsegv", &spu::tools::Signal_handler::reset_sigsegv);
}