#ifndef WRAPPER_ITERATOR_HPP_
#define WRAPPER_ITERATOR_HPP_

#include "wrapper/Common/pybind11_common.h"

#include <streampu.hpp>

namespace py = pybind11;
using namespace spu;
using namespace spu::module;

namespace pyspu
{
namespace wrapper
{
void
wrap_iterator(py::handle scope);
}
} // namespace pyspu

#endif // WRAPPER_ITERATOR_HPP_