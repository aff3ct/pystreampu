#ifndef WRAPPER_EXCEPTION_HPP__
#define WRAPPER_EXCEPTION_HPP__

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
void
wrap_exceptions(py::module_& scope);
}
} // namespace pyspu

#endif // WRAPPER_EXCEPTION_HPP__