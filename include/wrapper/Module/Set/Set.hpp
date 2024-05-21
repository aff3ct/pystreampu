#ifndef WRAPPER_SET_HPP_
#define WRAPPER_SET_HPP_

#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	void wrap_set(py::handle scope);
}
}
#endif //WRAPPER_SET_HPP_