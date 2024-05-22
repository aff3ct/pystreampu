#include "wrapper/Module/Unaryop/Unaryop.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_unaryop_not(py::handle scope) {
  UOP_WRAP(not, ALL_INT_DTYPES);
}