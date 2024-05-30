#ifndef WRAPPER_CONTROLLER_STATIC_HPP_
#define WRAPPER_CONTROLLER_STATIC_HPP_

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
void
wrap_controller_static(py::handle scope);
}
} // namespace pyaf

#endif // WRAPPER_CONTROLLER_STATIC_HPP_