#include "wrapper/Tools/Interface/Interface_get_set_n_frames.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;

void
pyaf::wrapper::wrap_interface_get_set_n_frames(py::module_& scope)
{
    auto itf_class = py::class_<spu::tools::Interface_get_set_n_frames,
                                pyaf::wrapper::py_Interface_get_set_n_frames,
                                std::unique_ptr<spu::tools::Interface_get_set_n_frames, py::nodelete>>(
      scope, "Interface_get_set_n_frames");

    itf_class.def_property("n_frames",
                           &spu::tools::Interface_get_set_n_frames::get_n_frames,
                           &spu::tools::Interface_get_set_n_frames::set_n_frames);
    // itf_class.def("get_n_frames",
    // &spu::tools::Interface_get_set_n_frames::get_n_frames);
    // itf_class.def("set_n_frames",
    // &spu::tools::Interface_get_set_n_frames::set_n_frames);
}