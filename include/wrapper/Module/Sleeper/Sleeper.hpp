#ifndef WRAPPER_SLEEPER_HPP_
#define WRAPPER_SLEEPER_HPP_

#include <pybind11/pybind11.h>

#include <streampu.hpp>

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;
using namespace spu;
using namespace spu::module;

namespace pyaf
{
namespace wrapper
{
void wrap_sleeper(py::handle scope);
}
}
#endif //WRAPPER_SLEEPER_HPP_