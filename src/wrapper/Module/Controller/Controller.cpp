#include "wrapper/Module/Controller/Controller.hpp"
#include "wrapper/Module/Controller/Cyclic/Controller_cyclic.hpp"
#include "wrapper/Module/Controller/Limit/Controller_limit.hpp"
#include "wrapper/Module/Controller/Static/Controller_static.hpp"

#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_functions.h"

namespace py = pybind11;
using namespace pyspu::wrapper;
using namespace py::literals;

void
pyspu::wrapper::wrap_controller(py::handle scope)
{
    auto py_controller_class =
      py::class_<spu::module::Controller, spu::module::Module, spu::tools::Interface_reset>(scope, "Controller");
    py_controller_class.def_property("path", &spu::module::Controller::get_path, &spu::module::Controller::set_path);
}

void
pyspu::wrapper::wrap_controllers(py::handle scope)
{
    pyspu::wrapper::wrap_controller(scope);
    pyspu::wrapper::wrap_controller_cyclic(scope);
    pyspu::wrapper::wrap_controller_limit(scope);
    pyspu::wrapper::wrap_controller_static(scope);
}