#ifndef WRAPPER_ITERATOR_HPP_
#define WRAPPER_ITERATOR_HPP_

#include <pybind11/pybind11.h>

#include <streampu.hpp>

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;
using namespace spu;
using namespace spu::module;

namespace pyaf {
namespace wrapper {
void wrap_iterator(py::handle scope);
}
} // namespace pyaf

#endif // WRAPPER_ITERATOR_HPP_