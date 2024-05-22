#include "wrapper/Module/Binaryop/Binaryop.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_binaryop_max(py::handle scope) {
  BOP_WRAP(max, ALL_DTYPES, ALL_DTYPES);
}