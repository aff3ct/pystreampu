#ifndef WRAPPER_PROBE_TIMESTAMP_HPP_
#define WRAPPER_PROBE_TIMESTAMP_HPP_

#include <aff3ct-core.hpp>
#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	void wrap_probe_timestamp(py::handle scope);
}
}
#endif //WRAPPER_PROBE_TIMESTAMP_HPP_