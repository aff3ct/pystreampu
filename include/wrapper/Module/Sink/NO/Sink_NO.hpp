#ifndef WRAPPER_SINK_NO_HPP_
#define WRAPPER_SINK_NO_HPP_

#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	void wrap_sink_no(py::handle scope);
}
}
#endif //WRAPPER_SINK_NO_HPP_