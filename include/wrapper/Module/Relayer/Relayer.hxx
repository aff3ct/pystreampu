#ifndef WRAPPER_RELAYER_HXX_
#define WRAPPER_RELAYER_HXX_

#include "wrapper/Module/Relayer/Relayer.hpp"
#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace spu;
using namespace spu::module;

namespace pyaf
{
namespace wrapper
{

template <typename T>
void wrap_relayer_internal(py::handle scope, const std::string& name)
{
    auto doc_str = R"pbdoc()pbdoc";
    auto py_relayer_class = py::class_<spu::module::Relayer<T>, spu::module::Module>(scope, name.c_str());

    py_relayer_class.def(py::init<const size_t, const size_t>(),"n_elmts"_a, "ns"_a = 0, doc_str, py::return_value_policy::take_ownership);
    py_relayer_class.def_property("ns", &spu::module::Relayer<T>::get_ns, &spu::module::Relayer<T>::set_ns);
    py_relayer_class.def_property_readonly("n_elmts", &spu::module::Relayer<T>::get_n_elmts);
}

}
}

#endif //WRAPPER_RELAYER_HXX_