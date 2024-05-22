#include "wrapper/Module/Reducer/Reducer.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_reducer_ne(py::handle scope) {
  RED_WRAP(ne, ALL_DTYPES, ALL_DTYPES);
}