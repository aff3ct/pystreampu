#ifndef WRAPPER_INCREMENTER_HXX_
#define WRAPPER_INCREMENTER_HXX_

#include "wrapper/Module/Incrementer/Incrementer.hpp"
#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace aff3ct;
using namespace aff3ct::module;

namespace pyaf
{
namespace wrapper
{

template <typename T>
void wrap_incrementer_internal(py::handle scope, const std::string& name)
{
    auto doc_str = R"pbdoc()pbdoc";
    auto py_incrementer_class = py::class_<aff3ct::module::Incrementer<T>, aff3ct::module::Module>(scope, name.c_str());

    py_incrementer_class.def(py::init<const size_t, const size_t>(),"n_elmts"_a, "ns"_a = 0, doc_str, py::return_value_policy::take_ownership);
    py_incrementer_class.def_property("ns", &aff3ct::module::Incrementer<T>::get_ns, &aff3ct::module::Incrementer<T>::set_ns);
    py_incrementer_class.def_property_readonly("n_elmts", &aff3ct::module::Incrementer<T>::get_n_elmts);
}

}
}

#endif //WRAPPER_INCREMENTER_HXX_