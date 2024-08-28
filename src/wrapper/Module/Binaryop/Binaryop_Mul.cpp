#include "wrapper/Module/Binaryop/Binaryop.hpp"

namespace py = pybind11;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_binaryop_mul(py::handle scope)
{
    BOP_WRAP(mul, ALL_DTYPES, ALL_DTYPES);
}