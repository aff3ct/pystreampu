#ifndef WRAPPER_uNARYOP_HPP_
#define WRAPPER_uNARYOP_HPP_

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
template<typename TI = int8_t, typename TO = int8_t, tools::proto_uop<TI, TO> UOP>
inline void
internal_wrap_unaryop(py::handle scope, const std::string& name);
inline void
wrap_unaryop(py::handle scope);

void
wrap_unaryop_abs(py::handle scope);
void
wrap_unaryop_not(py::handle scope);
void
wrap_unaryop_sign(py::handle scope);
void
wrap_unaryop_neg(py::handle scope);
void
wrap_unaryop_cast(py::handle scope);
// void wrap_unaryop_not_abs(py::handle scope);

} // namespace wrapper
} // namespace pyspu

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "wrapper/Module/Unaryop/Unaryop.hxx"
#endif

#endif // WRAPPER_uNARYOP_HPP_