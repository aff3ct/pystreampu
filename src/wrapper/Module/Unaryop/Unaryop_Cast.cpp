#include "wrapper/Module/Unaryop/Unaryop.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void
pyaf::wrapper::wrap_unaryop_cast(py::handle scope)
{
    UOP_WRAP(cast, ALL_DTYPES);
}