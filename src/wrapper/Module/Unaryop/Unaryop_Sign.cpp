#include "wrapper/Module/Unaryop/Unaryop.hpp"

namespace py = pybind11;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_unaryop_sign(py::handle scope)
{
    UOP_WRAP(sign, SIGNED_DTYPES);
}