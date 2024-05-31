#include "wrapper/Module/Reducer/Reducer.hpp"

namespace py = pybind11;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_reducer_lt(py::handle scope)
{
    RED_WRAP(lt, ALL_DTYPES, ALL_DTYPES);
}