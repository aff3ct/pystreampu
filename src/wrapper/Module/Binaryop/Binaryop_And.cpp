#include "wrapper/Module/Binaryop/Binaryop.hpp"

namespace py = pybind11;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_binaryop_and(py::handle scope)
{
    BOP_WRAP(and, ALL_INT_DTYPES, ALL_DTYPES);
}