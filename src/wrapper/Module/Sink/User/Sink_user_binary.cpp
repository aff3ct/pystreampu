#include "wrapper/Module/Sink/User/Sink_user_binary.hpp"
#include "wrapper/Common/Tools/Type/Type.hpp"

#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"
#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_sink_user_binary(py::handle scope) {
  using lB = tl::type_list<ALL_DTYPES>;
  lB::for_each([&](auto b) {
    using B = typename decltype(b)::type;
    std::string B_str = spu::runtime::type_to_string[typeid(B)];
    auto sink_class =
        py::class_<spu::module::Sink_user_binary<B>, spu::module::Sink<B>>(
            scope, std::string("Sink_user_binary_" + B_str).c_str());
    sink_class.def(py::init<const int, const std::string &>(),
                   "max_data_size"_a, "filename"_a,
                   py::return_value_policy::take_ownership);
  });
}