#include "wrapper/Module/Controller/Static/Controller_static.hpp"

#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_functions.h"

namespace py = pybind11;
using namespace pyspu::wrapper;
using namespace py::literals;

void
pyspu::wrapper::wrap_controller_static(py::handle scope)
{
    auto py_controller_static_class =
      py::class_<spu::module::Controller_static, spu::module::Controller>(scope, "Controller_static");
    py_controller_static_class.def(
      py::init<const size_t>(), "init_path"_a = 0, py::return_value_policy::take_ownership);
}