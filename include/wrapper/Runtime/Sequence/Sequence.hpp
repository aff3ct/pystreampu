#ifndef WRAPPER_SEQUENCE_HPP_
#define WRAPPER_SEQUENCE_HPP_

#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	void wrap_sequence(py::handle scope);
}
}
#endif //WRAPPER_SEQUENCE_HPP_