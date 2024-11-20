#ifndef WRAPPER_PROBE_LATENCY_HPP_
#define WRAPPER_PROBE_LATENCY_HPP_

#include "wrapper/Common/pybind11_common.h"
#include <streampu.hpp>
namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
void
wrap_probe_latency(py::handle scope);
}
} // namespace pyspu
#endif // WRAPPER_PROBE_LATENCY_HPP_