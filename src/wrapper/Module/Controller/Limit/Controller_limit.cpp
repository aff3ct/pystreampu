#include "wrapper/Module/Controller/Limit/Controller_limit.hpp"

#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_functions.h"

namespace py = pybind11;
using namespace pyspu::wrapper;
using namespace py::literals;

void
pyspu::wrapper::wrap_controller_limit(py::handle scope)
{
    auto py_controller_limit_class =
      py::class_<spu::module::Controller_limit, spu::module::Controller>(scope, "Controller_limit");
    py_controller_limit_class.def(
      py::init<const size_t, const size_t>(), "limit"_a, "init_path"_a = 0, py::return_value_policy::take_ownership);
}