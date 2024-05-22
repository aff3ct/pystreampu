#ifndef WRAPPER_INITIALIZER_HPP_
#define WRAPPER_INITIALIZER_HPP_

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <streampu.hpp>
#include <string>

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;
using namespace spu;
using namespace spu::module;

namespace pyaf {
namespace wrapper {
template <typename T = int8_t>
inline void wrap_initializer_internal(py::handle scope,
                                      const std::string &name);

void wrap_initializer(py::handle scope);
} // namespace wrapper
} // namespace pyaf

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "wrapper/Module/Initializer/Initializer.hxx"
#endif

#endif // WRAPPER_INITIALIZER_HPP_