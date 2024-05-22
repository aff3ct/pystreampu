#include "wrapper/Module/Unaryop/Unaryop.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_unaryop_abs(py::handle scope) {
  UOP_WRAP(abs, SIGNED_DTYPES);
}