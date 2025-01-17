#ifndef WRAPPER_INCREMENTER_HPP_
#define WRAPPER_INCREMENTER_HPP_

#include "wrapper/Common/pybind11_common.h"

#include <streampu.hpp>

namespace py = pybind11;
using namespace spu;
using namespace spu::module;

namespace pyspu
{
namespace wrapper
{
template<typename T = int>
inline void
wrap_incrementer_internal(py::handle scope, const std::string& name);

void
wrap_incrementer(py::handle scope);
} // namespace wrapper
} // namespace pyspu

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "wrapper/Module/Incrementer/Incrementer.hxx"
#endif

#endif // WRAPPER_INCREMENTER_HPP_