#include "wrapper/Module/Unaryop/Unaryop.hpp"

namespace py = pybind11;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_unaryop_abs(py::handle scope)
{
    UOP_WRAP(abs, SIGNED_DTYPES);
}