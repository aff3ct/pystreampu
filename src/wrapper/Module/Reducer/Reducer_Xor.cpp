#include "wrapper/Module/Reducer/Reducer.hpp"

namespace py = pybind11;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_reducer_xor(py::handle scope)
{
    RED_WRAP(xor, ALL_INT_DTYPES, ALL_DTYPES);
}