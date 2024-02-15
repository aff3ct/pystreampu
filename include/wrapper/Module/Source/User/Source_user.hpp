#ifndef WRAPPER_SOURCE_USER_HPP_
#define WRAPPER_SOURCE_USER_HPP_

#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	void wrap_source_user(py::handle scope);
}
}
#endif //WRAPPER_SOURCE_USER_HPP_