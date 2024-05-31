#ifndef WRAPPER_SINK_NO_HPP_
#define WRAPPER_SINK_NO_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
void
wrap_sink_no(py::handle scope);
}
} // namespace pyspu
#endif // WRAPPER_SINK_NO_HPP_