#ifndef WRAPPER_INITIALIZER_HPP_
#define WRAPPER_INITIALIZER_HPP_

#include "wrapper/Common/pybind11_common.h"

#include <streampu.hpp>
#include <string>

namespace py = pybind11;
using namespace spu;
using namespace spu::module;

namespace pyspu
{
namespace wrapper
{
template<typename T = int8_t>
inline void
wrap_initializer_internal(py::handle scope, const std::string& name);

void
wrap_initializer(py::handle scope);
} // namespace wrapper
} // namespace pyspu

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "wrapper/Module/Initializer/Initializer.hxx"
#endif

#endif // WRAPPER_INITIALIZER_HPP_