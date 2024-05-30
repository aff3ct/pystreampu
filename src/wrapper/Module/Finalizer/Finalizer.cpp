#include "wrapper/Module/Finalizer/Finalizer.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void
pyaf::wrapper::wrap_finalizer(py::handle scope)
{
    using int_lT = tl::type_list<ALL_DTYPES>;
    int_lT::for_each(
      [&](auto t)
      {
          using T = typename decltype(t)::type;
          std::string T_str = spu::runtime::type_to_string[typeid(T)];
          pyaf::wrapper::wrap_finalizer_internal<T>(scope, "Finalizer_" + T_str);
      });
}