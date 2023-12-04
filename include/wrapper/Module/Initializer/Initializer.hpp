#ifndef WRAPPER_INITIALIZER_HPP_
#define WRAPPER_INITIALIZER_HPP_

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>

#include <aff3ct-core.hpp>
#include <string>

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;
using namespace aff3ct;
using namespace aff3ct::module;

namespace pyaf
{
namespace wrapper
{
template <typename T = int8_t>
inline void wrap_initializer_internal(py::handle scope, const std::string& name);

void wrap_initializer(py::handle scope);
}
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "wrapper/Module/Initializer/Initializer.hxx"
#endif

#endif //WRAPPER_INITIALIZER_HPP_