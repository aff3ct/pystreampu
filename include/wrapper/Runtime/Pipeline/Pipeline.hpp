#ifndef WRAPPER_PIPELINE_HPP_
#define WRAPPER_PIPELINE_HPP_

#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
void
wrap_pipeline(py::handle scope);
}
} // namespace pyaf
#endif // WRAPPER_PIPELINE_HPP_