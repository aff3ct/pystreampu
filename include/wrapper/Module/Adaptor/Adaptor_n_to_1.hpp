#ifndef WRAPPER_ADAPTOR_N_TO_1_HPP_
#define WRAPPER_ADAPTOR_N_TO_1_HPP_

#include <pybind11/pybind11.h>

#include <aff3ct-core.hpp>

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;
using namespace aff3ct;
using namespace aff3ct::module;

namespace pyaf
{
namespace wrapper
{
void wrap_adaptor_n_to_1(py::handle scope);
}
}

#endif //WRAPPER_ADAPTOR_N_TO_1_HPP_