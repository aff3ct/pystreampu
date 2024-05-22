#ifndef WRAPPER_PROBE_THROUGHPUT_HPP_
#define WRAPPER_PROBE_THROUGHPUT_HPP_

#include <streampu.hpp>
#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	void wrap_probe_throughput(py::handle scope);
}
}
#endif //WRAPPER_PROBE_THROUGHPUT_HPP_