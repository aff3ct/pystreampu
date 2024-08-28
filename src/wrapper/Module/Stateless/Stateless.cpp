#include "wrapper/Module/Stateless/Stateless.hpp"

#include "wrapper/Common/Tools/type_functions.h"
#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>

namespace py = pybind11;
using namespace py::literals;

void
pyspu::wrapper::wrap_stateless(py::handle scope)
{
    auto stateless_class = py::class_<spu::module::Stateless, spu::module::Module>(scope,
                                                                                   "Stateless",
                                                                                   R"pbdoc(
    Stateless modules are modules that can be cloned automatically.
    )pbdoc");
    stateless_class.def(py::init<>(), "Build a Stateless module", py::return_value_policy::take_ownership);
    stateless_class.def_property("name", &spu::module::Stateless::get_name, &spu::module::Stateless::set_name);
}
