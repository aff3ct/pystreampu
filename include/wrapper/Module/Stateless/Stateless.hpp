#ifndef WRAPPER_STATELESS_HPP_
#define WRAPPER_STATELESS_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyaf {
namespace wrapper {
void wrap_stateless(py::handle scope);
}
} // namespace pyaf
#endif // WRAPPER_STATELESS_HPP_