#ifndef WRAPPER_ADAPTOR_N_TO_1_HPP_
#define WRAPPER_ADAPTOR_N_TO_1_HPP_

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
wrap_adaptor_n_to_1(py::handle scope);
}
} // namespace pyspu

#endif // WRAPPER_ADAPTOR_N_TO_1_HPP_