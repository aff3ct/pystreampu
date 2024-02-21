#ifndef WRAPPER_EXCEPTION_HPP__
#define WRAPPER_EXCEPTION_HPP__

#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	void wrap_exceptions(py::module_ &scope);
}
}

#endif // WRAPPER_EXCEPTION_HPP__