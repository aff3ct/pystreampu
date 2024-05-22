#ifndef WRAPPER_SIGNAL_HANDLER_HPP__
#define WRAPPER_SIGNAL_HANDLER_HPP__

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyaf {
namespace wrapper {
void wrap_signal_handler(py::module_ &scope);
}
} // namespace pyaf

#endif // WRAPPER_SIGNAL_HANDLER_HPP__