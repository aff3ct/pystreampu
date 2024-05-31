#ifndef WRAPPER_PROBE_THROUGHPUT_HPP_
#define WRAPPER_PROBE_THROUGHPUT_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>
namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
void
wrap_probe_throughput(py::handle scope);
}
} // namespace pyspu
#endif // WRAPPER_PROBE_THROUGHPUT_HPP_