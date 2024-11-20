#ifndef WRAPPER_INTERFACE_REPORTER_PROBE_HPP__
#define WRAPPER_INTERFACE_REPORTER_PROBE_HPP__

#include "wrapper/Common/pybind11_common.h"

#include <string>
#include <vector>

#include <streampu.hpp>

namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
void
wrap_reporter_probe(py::module_& scope);
}
} // namespace pyspu

#endif // WRAPPER_INTERFACE_REPORTER_PROBE_HPP__