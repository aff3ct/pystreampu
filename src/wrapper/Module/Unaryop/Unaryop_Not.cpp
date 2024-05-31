#include "wrapper/Module/Unaryop/Unaryop.hpp"

namespace py = pybind11;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_unaryop_not(py::handle scope)
{
    UOP_WRAP(not, ALL_INT_DTYPES);
}