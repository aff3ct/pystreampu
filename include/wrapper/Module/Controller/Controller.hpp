#ifndef WRAPPER_CONTROLLER_HPP_
#define WRAPPER_CONTROLLER_HPP_

#include "wrapper/Common/pybind11_common.h"

#include <streampu.hpp>

namespace py = pybind11;
using namespace spu;
using namespace spu::module;

namespace pyspu
{
namespace wrapper
{
void
wrap_controller(py::handle scope);
void
wrap_controllers(py::handle scope);
} // namespace wrapper
} // namespace pyspu

#include "Cyclic/Controller_cyclic.hpp"
#include "Limit/Controller_limit.hpp"
#include "Static/Controller_static.hpp"

#endif // WRAPPER_CONTROLLER_HPP_