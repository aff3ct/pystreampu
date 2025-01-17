#include "wrapper/Module/Source/User/Source_user_binary.hpp"
#include "wrapper/Common/Tools/Type/Type.hpp"

#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"
#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>

namespace py = pybind11;
using namespace py::literals;

void
pyspu::wrapper::wrap_source_user_binary(py::handle scope)
{
    using lB = tl::type_list<ALL_DTYPES>;
    lB::for_each(
      [&](auto b)
      {
          using B = typename decltype(b)::type;
          std::string B_str = spu::runtime::type_to_string[typeid(B)];
          auto source_class = py::class_<spu::module::Source_user_binary<B>, spu::module::Source<B>>(
            scope, std::string("Source_user_binary_" + B_str).c_str());
          source_class.def(py::init<const int, const std::string&, const bool, const bool>(),
                           "max_data_size"_a,
                           "filename"_a,
                           "auto_reset"_a = true,
                           "fifo_mode"_a = false,
                           py::return_value_policy::take_ownership);
      });
}