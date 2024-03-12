#ifndef WRAPPER_INTERFACE_REPORTER_PROBE_HPP__
#define WRAPPER_INTERFACE_REPORTER_PROBE_HPP__

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>
#include <string>

#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	void wrap_reporter_probe(py::module_ &scope);
}
}

#endif // WRAPPER_INTERFACE_REPORTER_PROBE_HPP__