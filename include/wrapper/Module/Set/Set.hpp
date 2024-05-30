#ifndef WRAPPER_SET_HPP_
#define WRAPPER_SET_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
void
wrap_set(py::handle scope);
}
} // namespace pyaf
#endif // WRAPPER_SET_HPP_