#include "wrapper/Tools/Interface/Interface_is_done.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_interface_is_done(py::module_& scope)
{
    auto itf_class =
      py::class_<spu::tools::Interface_is_done,
                 pyspu::wrapper::py_Interface_is_done,
                 std::unique_ptr<spu::tools::Interface_is_done, py::nodelete>>(scope, "Interface_is_done");
    itf_class.def("is_done", &spu::tools::Interface_is_done::is_done);
}