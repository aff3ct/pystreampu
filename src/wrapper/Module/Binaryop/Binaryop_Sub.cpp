#include "wrapper/Module/Binaryop/Binaryop.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_binaryop_sub(py::handle scope) {
  BOP_WRAP(sub, ALL_DTYPES, ALL_DTYPES);
}