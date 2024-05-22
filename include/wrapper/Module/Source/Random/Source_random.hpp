#ifndef WRAPPER_SOURCE_RANDOM_HPP_
#define WRAPPER_SOURCE_RANDOM_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyaf {
namespace wrapper {
void wrap_source_random(py::handle scope);
}
} // namespace pyaf
#endif // WRAPPER_SOURCE_RANDOM_HPP_