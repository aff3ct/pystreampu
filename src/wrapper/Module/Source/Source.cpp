#include "wrapper/Module/Source/Source.hpp"
#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_list.hpp"

#include "wrapper/Common/Tools/type_functions.h"
#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>

namespace py = pybind11;
using namespace py::literals;

void
pyaf::wrapper::wrap_source(py::handle scope)
{
    using lB = tl::type_list<ALL_DTYPES>;
    lB::for_each(
      [&](auto b)
      {
          using B = typename decltype(b)::type;
          std::string B_str = spu::runtime::type_to_string[typeid(B)];
          auto source_class = py::class_<spu::module::Source<B>,
                                         spu::module::Module,
                                         spu::tools::Interface_set_seed,
                                         spu::tools::Interface_is_done,
                                         spu::tools::Interface_reset>(scope, std::string("Source_" + B_str).c_str());
          source_class.def(py::init<const int>(), "max_data_size"_a, py::return_value_policy::take_ownership);
      });
}
