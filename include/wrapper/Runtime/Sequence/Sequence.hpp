#ifndef WRAPPER_SEQUENCE_HPP_
#define WRAPPER_SEQUENCE_HPP_

#include "wrapper/Common/pybind11_common.h"
namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
void
wrap_sequence(py::handle scope);
}
} // namespace pyspu
#endif // WRAPPER_SEQUENCE_HPP_