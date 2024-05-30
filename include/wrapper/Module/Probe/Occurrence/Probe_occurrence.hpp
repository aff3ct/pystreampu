#ifndef WRAPPER_PROBE_OCCURRENCE_HPP_
#define WRAPPER_PROBE_OCCURRENCE_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>
namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
void
wrap_probe_occurrence(py::handle scope);
}
} // namespace pyaf
#endif // WRAPPER_PROBE_OCCURRENCE_HPP_