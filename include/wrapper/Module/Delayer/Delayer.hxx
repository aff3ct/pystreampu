#ifndef WRAPPER_DELAYER_HXX_
#define WRAPPER_DELAYER_HXX_

#include "wrapper/Module/Delayer/Delayer.hpp"
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

template <typename D>
void wrap_delayer_internal(py::handle scope, const std::string& name)
{
    auto doc_str = R"pbdoc()pbdoc";
    auto py_delayer_class = py::class_<aff3ct::module::Delayer<D>, aff3ct::module::Module>(scope, name.c_str());
    py_delayer_class.def(py::init<const size_t, const D>(),"size"_a, "init_val"_a, doc_str, py::return_value_policy::take_ownership);

    py_delayer_class.def("set_data",
    [](aff3ct::module::Delayer<D> self, const std::vector<D>& data)
    {
        self.set_data(data);
    });
    py_delayer_class.def("set_data",
    [](aff3ct::module::Delayer<D> self, const D* data)
    {
        self.set_data(data);
    });
    py_delayer_class.def_property("n_frames", &aff3ct::module::Delayer<D>::get_n_frames, &aff3ct::module::Delayer<D>::set_n_frames);
}

}
}

#endif //WRAPPER_DELAYER_HXX_