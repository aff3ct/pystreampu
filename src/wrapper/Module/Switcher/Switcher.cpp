#include "wrapper/Module/Switcher/Switcher.hpp"
#include "wrapper/Common/Tools/Type/Type.hpp"

#include "wrapper/Common/Tools/type_functions.h"
#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_switcher(py::handle scope) {
  auto switcher_class =
      py::class_<spu::module::Switcher, spu::module::Module>(scope, "Switcher");
  switcher_class.def(
      py::init([](const size_t n_data_sockets, const size_t n_elmts_commute,
                  pyaf::dtype datatype_commute, const size_t n_elmts_select,
                  pyaf::dtype datatype_select) {
        std::type_index cpp_datatype_commute =
            pyaf::utils::str2typeid(datatype_commute.get_name());
        std::type_index cpp_datatype_select =
            pyaf::utils::str2typeid(datatype_select.get_name());
        return new spu::module::Switcher(n_data_sockets, n_elmts_commute,
                                         cpp_datatype_commute, n_elmts_select,
                                         cpp_datatype_select);
      }),
      "n_data_sockets"_a, "n_elmts_commute"_a, "datatype_commute"_a,
      "n_elmts_select"_a, "datatype_select"_a, R"pbdoc()pbdoc",
      py::return_value_policy::take_ownership);

  switcher_class.def(py::init([](const size_t n_data_sockets,
                                 const size_t n_elmts, pyaf::dtype datatype) {
                       std::type_index cpp_datatype =
                           pyaf::utils::str2typeid(datatype.get_name());
                       return new spu::module::Switcher(n_data_sockets, n_elmts,
                                                        cpp_datatype);
                     }),
                     "n_data_sockets"_a, "n_elmts"_a, "datatype"_a,
                     R"pbdoc()pbdoc", py::return_value_policy::take_ownership);
}
