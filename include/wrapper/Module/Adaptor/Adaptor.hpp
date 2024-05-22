#ifndef WRAPPER_ADAPTOR_HPP_
#define WRAPPER_ADAPTOR_HPP_

#include <pybind11/pybind11.h>

#include <streampu.hpp>

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;
using namespace spu;
using namespace spu::module;

namespace pyaf {
namespace wrapper {
void wrap_adaptor(py::handle scope);
void wrap_adaptors(py::handle scope);
} // namespace wrapper
} // namespace pyaf

#include "Adaptor_1_to_n.hpp"
#include "Adaptor_n_to_1.hpp"

#endif // WRAPPER_ADAPTOR_HPP_