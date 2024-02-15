#ifndef WRAPPER_STATELESS_HPP_
#define WRAPPER_STATELESS_HPP_

#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	void wrap_stateless(py::handle scope);
}
}
#endif //WRAPPER_STATELESS_HPP_