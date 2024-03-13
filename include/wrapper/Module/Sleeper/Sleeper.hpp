#ifndef WRAPPER_SLEEPER_HPP_
#define WRAPPER_SLEEPER_HPP_

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
void wrap_sleeper(py::handle scope);
}
}
#endif //WRAPPER_SLEEPER_HPP_