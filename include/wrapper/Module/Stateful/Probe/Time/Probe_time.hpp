#ifndef WRAPPER_PROBE_TIME_HPP_
#define WRAPPER_PROBE_TIME_HPP_

#include "wrapper/Common/pybind11_common.h"
#include <streampu.hpp>
namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
void
wrap_probe_time(py::handle scope);
}
} // namespace pyspu
#endif // WRAPPER_PROBE_TIME_HPP_