#include "wrapper/Module/Binaryop/Binaryop.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void
pyaf::wrapper::wrap_binaryop_gt(py::handle scope)
{
    BOP_WRAP(gt, ALL_DTYPES, ALL_DTYPES);
}