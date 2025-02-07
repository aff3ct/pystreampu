#ifndef WRAPPER_STATEFUL_HPP_
#define WRAPPER_STATEFUL_HPP_

#include "wrapper/Common/pybind11_common.h"
#include <streampu.hpp>

namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
void
wrap_stateful(py::handle scop);
}
} // namespace pyspu
#endif // WRAPPER_STATEFUL_HPP_
