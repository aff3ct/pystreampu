#include "wrapper/Tools/Terminal/Terminal.hpp"

#include "wrapper/Common/pystreambuf.h"
#include <pybind11/chrono.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;

void
pyaf::wrapper::wrap_terminal(py::module_& scope)
{
    auto ter_class = py::class_<spu::tools::Terminal, pyaf::wrapper::py_Terminal>(scope, "Terminal");
    auto sys = py::module::import("sys");
    ter_class.def(py::init<>());
    ter_class.def("legend", &spu::tools::Terminal::legend, "stream"_a = sys.attr("stdout"));
    ter_class.def("temp_report", &spu::tools::Terminal::temp_report);
    ter_class.def("final_report", &spu::tools::Terminal::final_report);
    ter_class.def("start_temp_report", &spu::tools::Terminal::start_temp_report);
    ter_class.def("stop_temp_report", &spu::tools::Terminal::start_temp_report);
    ter_class.def("report", &pyaf::wrapper::Publicist_Terminal::report);

    auto ter_std_class = py::class_<spu::tools::Terminal_std, spu::tools::Terminal>(scope, "Terminal_std");
    ter_std_class.def(py::init<const std::vector<spu::tools::Reporter*>&>(), "reporters"_a);
    ter_std_class.def_property_readonly("reporters", &spu::tools::Terminal_std::get_reporters);

    auto ter_dmp_class = py::class_<spu::tools::Terminal_dump, spu::tools::Terminal_std>(scope, "Terminal_dump");
    ter_dmp_class.def(py::init<const std::vector<spu::tools::Reporter*>&>(), "reporters"_a);
}