#ifndef WRAPPER_CONTROLLER_HPP_
#define WRAPPER_CONTROLLER_HPP_

#include <pybind11/pybind11.h>

#include <aff3ct-core.hpp>

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;
using namespace aff3ct;
using namespace aff3ct::module;

namespace pyaf
{
namespace wrapper
{
void wrap_controller (py::handle scope);
void wrap_controllers(py::handle scope);
}
}

#include "Cyclic/Controller_cyclic.hpp"
#include "Limit/Controller_limit.hpp"
#include "Static/Controller_static.hpp"

#endif //WRAPPER_CONTROLLER_HPP_