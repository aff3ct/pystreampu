#include "wrapper/Module/Controller/Cyclic/Controller_cyclic.hpp"

#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/Type/Type.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;
using namespace py::literals;

void pyaf::wrapper::wrap_controller_cyclic(py::handle scope)
{
    auto py_controller_cyclic_class = py::class_<aff3ct::module::Controller_cyclic, aff3ct::module::Controller>(scope, "Controller_cyclic");
    py_controller_cyclic_class.def(py::init<const size_t, const size_t>(), "n_paths"_a, "init_path"_a=0, py::return_value_policy::take_ownership);

    py_controller_cyclic_class.def_property("path", &aff3ct::module::Controller_cyclic::get_path, &aff3ct::module::Controller_cyclic::set_path);
    py_controller_cyclic_class.def("set_n_paths", &aff3ct::module::Controller_cyclic::set_n_paths);
}