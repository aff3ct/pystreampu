#ifndef WRAPPER_BINARYOP_HPP_
#define WRAPPER_BINARYOP_HPP_

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/stl.h>

#include <streampu.hpp>
#include <string>

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;
using namespace spu;
using namespace spu::module;

namespace pyspu
{
namespace wrapper
{
template<typename TI = int8_t, typename TO = int8_t, tools::proto_bop<TI, TO> BOP = tools::bop_add<TI, TO>>
inline void
internal_wrap_binaryop(py::handle scope, const std::string& name);
inline void
wrap_binaryop(py::handle scope);

void
wrap_binaryop_add(py::handle scope);
void
wrap_binaryop_sub(py::handle scope);
void
wrap_binaryop_mul(py::handle scope);
void
wrap_binaryop_div(py::handle scope);
void
wrap_binaryop_min(py::handle scope);
void
wrap_binaryop_max(py::handle scope);
void
wrap_binaryop_le(py::handle scope);
void
wrap_binaryop_lt(py::handle scope);
void
wrap_binaryop_ge(py::handle scope);
void
wrap_binaryop_gt(py::handle scope);
void
wrap_binaryop_ne(py::handle scope);
void
wrap_binaryop_eq(py::handle scope);
void
wrap_binaryop_and(py::handle scope);
void
wrap_binaryop_or(py::handle scope);
void
wrap_binaryop_xor(py::handle scope);
} // namespace wrapper
} // namespace pyspu

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "wrapper/Module/Binaryop/Binaryop.hxx"
#endif

#endif // WRAPPER_BINARYOP_HPP_