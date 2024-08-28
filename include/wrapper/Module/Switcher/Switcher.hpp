#ifndef WRAPPER_SWITCHER_HPP_
#define WRAPPER_SWITCHER_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
void
wrap_switcher(py::handle scope);
}
} // namespace pyspu
#endif // WRAPPER_SWITCHER_HPP_