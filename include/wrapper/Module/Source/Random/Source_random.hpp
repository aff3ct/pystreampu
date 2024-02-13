#ifndef WRAPPER_SOURCE_RANDOM_HPP_
#define WRAPPER_SOURCE_RANDOM_HPP_

#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	void wrap_source_random(py::handle scope);
}
}
#endif //WRAPPER_SOURCE_RANDOM_HPP_