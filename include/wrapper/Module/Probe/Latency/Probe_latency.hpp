#ifndef WRAPPER_PROBE_LATENCY_HPP_
#define WRAPPER_PROBE_LATENCY_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>
namespace py = pybind11;

namespace pyaf {
namespace wrapper {
void wrap_probe_latency(py::handle scope);
}
} // namespace pyaf
#endif // WRAPPER_PROBE_LATENCY_HPP_