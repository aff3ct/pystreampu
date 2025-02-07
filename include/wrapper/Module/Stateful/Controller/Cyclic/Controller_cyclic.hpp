#ifndef WRAPPER_CONTROLLER_CYCLIC_HPP_
#define WRAPPER_CONTROLLER_CYCLIC_HPP_

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
wrap_controller_cyclic(py::handle scope);
}
} // namespace pyspu

#endif // WRAPPER_CONTROLLER_CYCLIC_HPP_