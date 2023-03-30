#include "wrapper/Module/Reducer/Reducer.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_reducer_le(py::handle scope)
{
	RED_WRAP(le, ALL_DTYPES, ALL_DTYPES);
}