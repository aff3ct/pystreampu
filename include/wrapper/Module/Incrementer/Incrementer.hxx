#ifndef WRAPPER_INCREMENTER_HXX_
#define WRAPPER_INCREMENTER_HXX_

#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"
#include "wrapper/Module/Incrementer/Incrementer.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace spu;
using namespace spu::module;

namespace pyspu
{
namespace wrapper
{

template<typename T>
void
wrap_incrementer_internal(py::handle scope, const std::string& name)
{
    auto doc_str = R"pbdoc()pbdoc";
    auto py_incrementer_class = py::class_<spu::module::Incrementer<T>, spu::module::Module>(scope, name.c_str());

    py_incrementer_class.def(py::init<const size_t, const size_t>(),
                             "n_elmts"_a,
                             "ns"_a = 0,
                             doc_str,
                             py::return_value_policy::take_ownership);
    py_incrementer_class.def_property("ns", &spu::module::Incrementer<T>::get_ns, &spu::module::Incrementer<T>::set_ns);
    py_incrementer_class.def_property_readonly("n_elmts", &spu::module::Incrementer<T>::get_n_elmts);
}

} // namespace wrapper
} // namespace pyspu

#endif // WRAPPER_INCREMENTER_HXX_