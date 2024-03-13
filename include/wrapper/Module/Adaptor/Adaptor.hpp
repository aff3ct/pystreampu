#ifndef WRAPPER_ADAPTOR_HPP_
#define WRAPPER_ADAPTOR_HPP_

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
void wrap_adaptor (py::handle scope);
void wrap_adaptors(py::handle scope);
}
}

#include "Adaptor_1_to_n.hpp"
#include "Adaptor_n_to_1.hpp"

#endif //WRAPPER_ADAPTOR_HPP_