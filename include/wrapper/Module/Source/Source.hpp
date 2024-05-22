#ifndef WRAPPER_SOURCE_HPP_
#define WRAPPER_SOURCE_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	void wrap_source(py::handle scope);
}
}
#endif //WRAPPER_SOURCE_HPP_