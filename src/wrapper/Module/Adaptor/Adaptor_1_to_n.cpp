#include "wrapper/Module/Adaptor/Adaptor_1_to_n.hpp"
#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_functions.h"

namespace py = pybind11;
using namespace pyspu::wrapper;
using namespace py::literals;

void
pyspu::wrapper::wrap_adaptor_1_to_n(py::handle scope)
{
    auto py_adaptor_1_to_n_class =
      py::class_<spu::module::Adaptor_1_to_n, spu::module::Adaptor>(scope, "Adaptor_1_to_n");

    py_adaptor_1_to_n_class.def(
      py::init(
        [](const size_t n_elemts, pyspu::dtype datatype, const size_t buffer_size, const bool active_waiting)
        {
            std::type_index cpp_datatype = pyspu::utils::str2typeid(datatype.get_name());
            return new spu::module::Adaptor_1_to_n(n_elemts, cpp_datatype, buffer_size, active_waiting);
        }),
      "n_elemts"_a,
      "datatype"_a,
      "buffer_size"_a = 1,
      "active_waiting"_a = true,
      R"pbdoc()pbdoc",
      py::return_value_policy::take_ownership);

    py_adaptor_1_to_n_class.def(py::init(
                                  [](const std::vector<size_t>& n_elemts,
                                     std::vector<pyspu::dtype> datatype,
                                     const size_t buffer_size,
                                     const bool active_waiting)
                                  {
                                      std::vector<std::type_index> cpp_datatype;
                                      for (auto& dt : datatype)
                                      {
                                          cpp_datatype.push_back(pyspu::utils::str2typeid(dt.get_name()));
                                      }
                                      return new spu::module::Adaptor_1_to_n(
                                        n_elemts, cpp_datatype, buffer_size, active_waiting);
                                  }),
                                "n_elemts"_a,
                                "datatype"_a,
                                "buffer_size"_a = 1,
                                "active_waiting"_a = true,
                                R"pbdoc()pbdoc",
                                py::return_value_policy::take_ownership);
}