#ifndef WRAPPER_SET_HPP_
#define WRAPPER_SET_HPP_

#include "wrapper/Common/pybind11_common.h"
#include <streampu.hpp>

namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
void
wrap_set(py::handle scope);
}
} // namespace pyspu
#endif // WRAPPER_SET_HPP_