#include "wrapper/Module/Delayer/Delayer.hpp"

namespace py = pybind11;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_delayer(py::handle scope)
{
    using int_lT = tl::type_list<ALL_DTYPES>;
    int_lT::for_each(
      [&](auto t)
      {
          using T = typename decltype(t)::type;
          std::string T_str = spu::runtime::type_to_string[typeid(T)];
          pyspu::wrapper::wrap_delayer_internal<T>(scope, "Delayer_" + T_str);
      });
}