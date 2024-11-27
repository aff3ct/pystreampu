#ifndef WRAPPER_INITIALIZER_HXX_
#define WRAPPER_INITIALIZER_HXX_

#include "wrapper/Module/Initializer/Initializer.hpp"
#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"

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
wrap_initializer_internal(py::handle scope, const std::string& name)
{
    auto doc_str = R"pbdoc()pbdoc";
    auto py_initializer_class = py::class_<spu::module::Initializer<T>, spu::module::Module>(scope, name.c_str());
    py_initializer_class.def(py::init<const size_t>(), "n_elmts"_a, doc_str, py::return_value_policy::take_ownership);
    py_initializer_class.def("get_init_data", &spu::module::Initializer<T>::get_init_data);
    // py_initializer_class.def("set_data", [](spu::module::Initializer<T> self,
    // const std::vector<std::vector<T>>& data){
    //     self.set_init_data(data);});
    // py_initializer_class.def("set_data", [](spu::module::Initializer<T> self,
    // const std::vector<T>& data)             {
    //     self.set_init_data(data);},py::keep_alive<1, 2>());
    py_initializer_class.def_property_readonly("data_init",
                                               [](const spu::module::Initializer<T>& self)
                                               {
                                                   const std::vector<std::vector<T>>& init_data = self.get_init_data();
                                                   py::list lst_out;
                                                   for (auto& v : init_data)
                                                       lst_out.append(
                                                         py::array{ (ssize_t)v.size(), (T*)v.data(), py::cast(self) });
                                                   return lst_out;
                                               });
    py_initializer_class.def_property(
      "n_frames", &spu::module::Initializer<T>::get_n_frames, &spu::module::Initializer<T>::set_n_frames);
}

} // namespace wrapper
} // namespace pyspu

#endif // WRAPPER_INITIALIZER_HXX_