#ifndef WRAPPER_ITERATOR_HPP_
#define WRAPPER_ITERATOR_HPP_

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
void wrap_iterator(py::handle scope);
}
}

#endif //WRAPPER_ITERATOR_HPP_