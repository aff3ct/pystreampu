#ifndef WRAPPER_SSEQ_HPP_
#define WRAPPER_SSEQ_HPP_

#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	void wrap_subsequence(py::handle scope);
}
}
#endif //WRAPPER_SSEQ_HPP_