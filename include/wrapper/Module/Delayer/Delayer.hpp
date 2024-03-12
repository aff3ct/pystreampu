#ifndef WRAPPER_DELAYER_HPP_
#define WRAPPER_DELAYER_HPP_

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
template <typename T = int>
inline void wrap_delayer_internal(py::handle scope, const std::string& name);

void wrap_delayer(py::handle scope);
}
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "wrapper/Module/Delayer/Delayer.hxx"
#endif

#endif //WRAPPER_DELAYER_HPP_