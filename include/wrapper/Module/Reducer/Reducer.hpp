#ifndef WRAPPER_REDUCER_HPP_
#define WRAPPER_REDUCER_HPP_

#include "wrapper/Common/pybind11_common.h"

#include <streampu.hpp>
#include <string>

namespace py = pybind11;
using namespace spu;

namespace pyspu
{
namespace wrapper
{
template<typename TI = int8_t, typename TO = int8_t, tools::proto_bop<TI, TO> BOP = tools::bop_add<TI, TO>>
inline void
internal_wrap_reducer(py::handle scope, const std::string& name);
inline void
wrap_reducer(py::handle scope);

void
wrap_reducer_add(py::handle scope);
void
wrap_reducer_sub(py::handle scope);
void
wrap_reducer_mul(py::handle scope);
void
wrap_reducer_div(py::handle scope);
void
wrap_reducer_min(py::handle scope);
void
wrap_reducer_max(py::handle scope);
void
wrap_reducer_le(py::handle scope);
void
wrap_reducer_lt(py::handle scope);
void
wrap_reducer_ge(py::handle scope);
void
wrap_reducer_gt(py::handle scope);
void
wrap_reducer_ne(py::handle scope);
void
wrap_reducer_eq(py::handle scope);
void
wrap_reducer_and(py::handle scope);
void
wrap_reducer_or(py::handle scope);
void
wrap_reducer_xor(py::handle scope);
} // namespace wrapper
} // namespace pyspu

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "wrapper/Module/Reducer/Reducer.hxx"
#endif

#endif // WRAPPER_REDUCER_HPP_