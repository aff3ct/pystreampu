#include "wrapper/Module/Binaryop/Binaryop.hpp"

namespace py = pybind11;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_binaryop_xor(py::handle scope)
{
    BOP_WRAP(xor, ALL_INT_DTYPES, ALL_DTYPES);
}