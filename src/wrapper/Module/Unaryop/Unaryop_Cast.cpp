#include "wrapper/Module/Unaryop/Unaryop.hpp"

namespace py = pybind11;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_unaryop_cast(py::handle scope)
{
    UOP_WRAP(cast, ALL_DTYPES);
}