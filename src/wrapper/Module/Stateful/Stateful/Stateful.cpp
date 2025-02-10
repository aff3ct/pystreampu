#include "wrapper/Module/Stateful/Stateful/Stateful.hpp"

namespace py = pybind11;
using namespace py::literals;

void
pyspu::wrapper::wrap_stateful(py::handle scope)
{
    auto stateful_class = py::class_<spu::module::Stateful, spu::module::Module>(scope,"Stateful",
                                                                                        R"pbdoc(
        Stateful modules are modules that cannot be cloned due to internal state                                                                            
        )pbdoc")
        .def(py::init<>());
}
