#ifndef WRAPPER_RELAYER_HPP_
#define WRAPPER_RELAYER_HPP_

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
inline void wrap_relayer_internal(py::handle scope, const std::string& name);

void wrap_relayer(py::handle scope);
}
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "wrapper/Module/Relayer/Relayer.hxx"
#endif

#endif //WRAPPER_RELAYER_HPP_