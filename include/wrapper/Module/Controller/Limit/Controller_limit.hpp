#ifndef WRAPPER_CONTROLLER_LIMIT_HPP_
#define WRAPPER_CONTROLLER_LIMIT_HPP_

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
wrap_controller_limit(py::handle scope);
}
} // namespace pyspu

#endif // WRAPPER_CONTROLLER_LIMIT_HPP_