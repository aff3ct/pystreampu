#ifndef WRAPPER_SLEEPER_HPP_
#define WRAPPER_SLEEPER_HPP_

#include <pybind11/pybind11.h>

#include <streampu.hpp>

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;
using namespace spu;
using namespace spu::module;

namespace pyspu
{
namespace wrapper
{
void
wrap_sleeper(py::handle scope);
}
} // namespace pyspu
#endif // WRAPPER_SLEEPER_HPP_