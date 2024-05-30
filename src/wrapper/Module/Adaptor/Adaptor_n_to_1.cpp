#include "wrapper/Module/Adaptor/Adaptor_n_to_1.hpp"
#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_functions.h"

namespace py = pybind11;
using namespace pyaf::wrapper;
using namespace py::literals;

void
pyaf::wrapper::wrap_adaptor_n_to_1(py::handle scope)
{
    auto py_adaptor_n_to_1_class =
      py::class_<spu::module::Adaptor_n_to_1, spu::module::Adaptor>(scope, "Adaptor_n_to_1");

    py_adaptor_n_to_1_class.def(
      py::init(
        [](const size_t n_elemts, pyaf::dtype datatype, const size_t buffer_size, const bool active_waiting)
        {
            std::type_index cpp_datatype = pyaf::utils::str2typeid(datatype.get_name());
            return new spu::module::Adaptor_n_to_1(n_elemts, cpp_datatype, buffer_size, active_waiting);
        }),
      "n_elemts"_a,
      "datatype"_a,
      "buffer_size"_a = 1,
      "active_waiting"_a = true,
      R"pbdoc()pbdoc",
      py::return_value_policy::take_ownership);

    py_adaptor_n_to_1_class.def(py::init(
                                  [](const std::vector<size_t>& n_elemts,
                                     std::vector<pyaf::dtype> datatype,
                                     const size_t buffer_size,
                                     const bool active_waiting)
                                  {
                                      std::vector<std::type_index> cpp_datatype;
                                      for (auto& dt : datatype)
                                      {
                                          cpp_datatype.push_back(pyaf::utils::str2typeid(dt.get_name()));
                                      }
                                      return new spu::module::Adaptor_n_to_1(
                                        n_elemts, cpp_datatype, buffer_size, active_waiting);
                                  }),
                                "n_elemts"_a,
                                "datatype"_a,
                                "buffer_size"_a = 1,
                                "active_waiting"_a = true,
                                R"pbdoc()pbdoc",
                                py::return_value_policy::take_ownership);
}