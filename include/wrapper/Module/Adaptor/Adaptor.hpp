#ifndef WRAPPER_ADAPTOR_HPP_
#define WRAPPER_ADAPTOR_HPP_

#include "wrapper/Common/pybind11_common.h"

#include <streampu.hpp>

namespace py = pybind11;
using namespace spu;
using namespace spu::module;

namespace pyspu
{
namespace wrapper
{
void
wrap_adaptor(py::handle scope);
void
wrap_adaptors(py::handle scope);
} // namespace wrapper
} // namespace pyspu

#include "Adaptor_1_to_n.hpp"
#include "Adaptor_n_to_1.hpp"

#endif // WRAPPER_ADAPTOR_HPP_