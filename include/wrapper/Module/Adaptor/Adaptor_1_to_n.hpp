#ifndef WRAPPER_ADAPTOR_1_TO_N_HPP_
#define WRAPPER_ADAPTOR_1_TO_N_HPP_

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
void wrap_adaptor_1_to_n(py::handle scope);
}
}

#endif //WRAPPER_ADAPTOR_1_TO_N_HPP_