#include "wrapper/Module/Controller/Limit/Controller_limit.hpp"

#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/Type/Type.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;
using namespace py::literals;

void pyaf::wrapper::wrap_controller_limit(py::handle scope)
{
    auto py_controller_limit_class = py::class_<aff3ct::module::Controller_limit, aff3ct::module::Controller>(scope, "Controller_limit");
    py_controller_limit_class.def(py::init<const size_t,const size_t>(), "limit"_a, "init_path"_a=0, py::return_value_policy::take_ownership);
}