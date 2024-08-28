#include "wrapper/Module/Reducer/Reducer.hpp"

namespace py = pybind11;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_reducer_sub(py::handle scope)
{
    RED_WRAP(sub, ALL_DTYPES, ALL_DTYPES);
}