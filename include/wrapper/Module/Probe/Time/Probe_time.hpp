#ifndef WRAPPER_PROBE_TIME_HPP_
#define WRAPPER_PROBE_TIME_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>
namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
void
wrap_probe_time(py::handle scope);
}
} // namespace pyaf
#endif // WRAPPER_PROBE_TIME_HPP_