#include "wrapper/Module/Reducer/Reducer.hpp"

namespace py = pybind11;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_reducer_and(py::handle scope)
{
    RED_WRAP(and, ALL_INT_DTYPES, ALL_DTYPES);
}