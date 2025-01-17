#ifndef WRAPPER_BINARYOP_HXX_
#define WRAPPER_BINARYOP_HXX_

#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"
#include "wrapper/Module/Binaryop/Binaryop.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace spu;
using namespace spu::module;

#define BOP_WRAP(name, TIlist, TOlist)                                                                                 \
    using lTI = tl::type_list<TIlist>;                                                                                 \
    using lTO = tl::type_list<TOlist>;                                                                                 \
    lTI::for_each(                                                                                                     \
      [&](auto ti)                                                                                                     \
      {                                                                                                                \
          using TI = typename decltype(ti)::type;                                                                      \
          std::string TI_str = spu::runtime::type_to_string[typeid(TI)];                                               \
          lTO::for_each(                                                                                               \
            [&](auto to)                                                                                               \
            {                                                                                                          \
                using TO = typename decltype(to)::type;                                                                \
                std::string TO_str = spu::runtime::type_to_string[typeid(TO)];                                         \
                pyspu::wrapper::internal_wrap_binaryop<TI, TO, spu::tools::bop_##name<TI, TO>>(                         \
                  scope, "Binaryop_" + std::string(#name) + "_" + TI_str + "_" + TO_str);                              \
            });                                                                                                        \
      });

namespace pyspu
{
namespace wrapper
{

template<typename TI, typename TO, tools::proto_bop<TI, TO> BOP>
void
internal_wrap_binaryop(py::handle scope, const std::string& name)
{
    auto doc_str = R"pbdoc()pbdoc";
    auto py_bop_class = py::class_<spu::module::Binaryop<TI, TO, BOP>, spu::module::Module>(scope, name.c_str());
    py_bop_class.def(
      py::init<const size_t, const size_t>(), "n_in1"_a, "n_in2"_a, doc_str, py::return_value_policy::take_ownership);
    py_bop_class.def(py::init<const size_t>(), "n_elmts"_a, doc_str, py::return_value_policy::take_ownership);
}

void
wrap_binaryop(py::handle scope)
{
    pyspu::wrapper::wrap_binaryop_add(scope);
    pyspu::wrapper::wrap_binaryop_sub(scope);
    pyspu::wrapper::wrap_binaryop_mul(scope);
    pyspu::wrapper::wrap_binaryop_div(scope);
    pyspu::wrapper::wrap_binaryop_min(scope);
    pyspu::wrapper::wrap_binaryop_max(scope);
    pyspu::wrapper::wrap_binaryop_le(scope);
    pyspu::wrapper::wrap_binaryop_lt(scope);
    pyspu::wrapper::wrap_binaryop_ge(scope);
    pyspu::wrapper::wrap_binaryop_gt(scope);
    pyspu::wrapper::wrap_binaryop_ne(scope);
    pyspu::wrapper::wrap_binaryop_eq(scope);

    pyspu::wrapper::wrap_binaryop_and(scope);
    pyspu::wrapper::wrap_binaryop_or(scope);
    pyspu::wrapper::wrap_binaryop_xor(scope);
}

} // namespace wrapper
} // namespace pyspu

#endif // WRAPPER_BINARYOP_HXX_