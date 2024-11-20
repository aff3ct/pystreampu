#include "wrapper/Module/Array/Array.hpp"

#include <string>
namespace py = pybind11;
using namespace py::literals;
using namespace spu::module;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_array(py::module_& scope)
{
    using lTI = tl::type_list<ALL_DTYPES>;
    lTI::for_each(
      [&](auto ti)
      {
          using TI = typename decltype(ti)::type;
          std::string TI_str = spu::runtime::type_to_string[typeid(TI)];
          auto arra_py_class =
            py::class_<spu::module::Array<TI>, spu::module::Module>(scope, std::string("Array_" + TI_str).c_str());

          arra_py_class.def(py::init<py::array_t<TI>&>(),
                            "data"_a,
                            py::keep_alive<1, 2>(),
                            R"pbdoc()pbdoc",
                            py::return_value_policy::take_ownership);
          // arra_py_class.def(py::init<const std::vector<TI>&, const
          // int>(),"frame"_a, "n_frames"_a=1, R"pbdoc()pbdoc",
          // py::return_value_policy::take_ownership);
          // arra_py_class.def(py::init<const
          // std::vector<std::vector<TI>>&>(),"frames"_a, R"pbdoc()pbdoc",
          // py::return_value_policy::take_ownership);
      });
}

template<typename T>
Array<T>::Array(py::array_t<T>& data)
  : Module()
  , dataptr(data.request().ptr)
{
    const std::string name = "Array";
    this->set_name(name);

    py::buffer_info data_buff = data.request();

    size_t data_sz = 0;

    if (data_buff.ndim == 1)
    {
        this->set_n_frames(1);
        data_sz = data_buff.shape[0];
    }
    else if (data_buff.ndim == 2)
    {
        this->set_n_frames(data_buff.shape[0]);
        data_sz = data_buff.shape[1];
    }

    this->set_single_wave(true);

    auto& p = this->create_task("read");
    auto ps_x = this->template create_socket_fwd<T>(p, "data", data_sz);
    p[ps_x].bind(data.request().ptr);

    this->create_codelet(
      p, [](Module& m, runtime::Task& t, const size_t frame_id) -> int { return runtime::status_t::SUCCESS; });
}

template<typename T>
void*
Array<T>::get_dataptr() const
{
    return this->dataptr;
}

template<typename T>
Array<T>*
Array<T>::clone() const
{
    auto m = new Array<T>(*this);
    m->deep_copy(*this);
    return m;
}

template class spu::module::Array<int8_t>;
template class spu::module::Array<uint8_t>;
template class spu::module::Array<int16_t>;
template class spu::module::Array<uint16_t>;
template class spu::module::Array<int32_t>;
template class spu::module::Array<uint32_t>;
template class spu::module::Array<int64_t>;
template class spu::module::Array<uint64_t>;
template class spu::module::Array<float>;
template class spu::module::Array<double>;