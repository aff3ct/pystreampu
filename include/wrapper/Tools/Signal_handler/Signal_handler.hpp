#ifndef WRAPPER_SIGNAL_HANDLER_HPP__
#define WRAPPER_SIGNAL_HANDLER_HPP__

#include "wrapper/Common/pybind11_common.h"
#include <streampu.hpp>

namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
void
wrap_signal_handler(py::module_& scope);
}
} // namespace pyspu

#endif // WRAPPER_SIGNAL_HANDLER_HPP__