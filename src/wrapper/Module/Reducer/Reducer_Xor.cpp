#include "wrapper/Module/Reducer/Reducer.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void
pyaf::wrapper::wrap_reducer_xor(py::handle scope)
{
    RED_WRAP(xor, ALL_INT_DTYPES, ALL_DTYPES);
}