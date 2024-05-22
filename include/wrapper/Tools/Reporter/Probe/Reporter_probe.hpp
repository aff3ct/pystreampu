#ifndef WRAPPER_INTERFACE_REPORTER_PROBE_HPP__
#define WRAPPER_INTERFACE_REPORTER_PROBE_HPP__

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>
#include <vector>

#include <streampu.hpp>

namespace py = pybind11;

namespace pyaf {
namespace wrapper {
void wrap_reporter_probe(py::module_ &scope);
}
} // namespace pyaf

#endif // WRAPPER_INTERFACE_REPORTER_PROBE_HPP__