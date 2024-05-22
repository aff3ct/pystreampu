#ifndef WRAPPER_INCREMENTER_HPP_
#define WRAPPER_INCREMENTER_HPP_

#include <pybind11/pybind11.h>

#include <streampu.hpp>

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;
using namespace spu;
using namespace spu::module;

namespace pyaf
{
namespace wrapper
{
template <typename T = int>
inline void wrap_incrementer_internal(py::handle scope, const std::string& name);

void wrap_incrementer(py::handle scope);
}
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "wrapper/Module/Incrementer/Incrementer.hxx"
#endif

#endif //WRAPPER_INCREMENTER_HPP_