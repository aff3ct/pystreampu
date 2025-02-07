#ifndef WRAPPER_SINK_HPP_
#define WRAPPER_SINK_HPP_

#include "wrapper/Common/pybind11_common.h"
#include <streampu.hpp>

namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
void
wrap_sinks(py::handle scope);
void
wrap_sink(py::handle scope);
} // namespace wrapper
} // namespace pyspu
#endif // WRAPPER_SINK_HPP_