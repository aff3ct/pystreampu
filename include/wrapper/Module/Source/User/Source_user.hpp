#ifndef WRAPPER_SOURCE_USER_HPP_
#define WRAPPER_SOURCE_USER_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
void
wrap_source_user(py::handle scope);
}
} // namespace pyspu
#endif // WRAPPER_SOURCE_USER_HPP_