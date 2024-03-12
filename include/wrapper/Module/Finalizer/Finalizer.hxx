#ifndef WRAPPER_Finalizer_HXX_
#define WRAPPER_Finalizer_HXX_

#include "wrapper/Module/Finalizer/Finalizer.hpp"
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
void wrap_finalizer_internal(py::handle scope, const std::string& name)
{
    auto doc_str = R"pbdoc()pbdoc";
    auto py_finalizer_class = py::class_<aff3ct::module::Finalizer<T>, aff3ct::module::Module>(scope, name.c_str());
    py_finalizer_class.def(py::init<const size_t>(),"n_elmts"_a, doc_str, py::return_value_policy::take_ownership);
    py_finalizer_class.def_property_readonly("final_data", &aff3ct::module::Finalizer<T>::get_final_data);
    py_finalizer_class.def_property("n_frames", &aff3ct::module::Finalizer<T>::get_n_frames, &aff3ct::module::Finalizer<T>::set_n_frames);
}

}
}

#endif //WRAPPER_Finalizer_HXX_