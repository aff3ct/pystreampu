#include "wrapper/Module/Binaryop/Binaryop.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_binaryop_or(py::handle scope)
{
	BOP_WRAP(or, ALL_INT_DTYPES, ALL_DTYPES);
}