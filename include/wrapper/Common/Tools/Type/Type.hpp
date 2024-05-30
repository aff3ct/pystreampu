#ifndef TYPE_HPP_
#define TYPE_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>
#include <type_traits>

#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"
#include <string>

namespace py = pybind11;
using namespace py::literals;

namespace pyaf
{

// Class for handling scalar StreamPU data types
class dtype
{
  protected:
    std::string name;
    int size;
    bool _signed;
    bool _floating_point;

  protected:
    explicit dtype(const std::string& name, const int size, const bool _signed, const bool _floating_point)
      : name(name)
      , size(size)
      , _signed(_signed)
      , _floating_point(_floating_point) {};

  public:
    std::string get_name() const { return this->name; }

    int get_size() const { return this->size; }

    bool is_signed() const { return this->_signed; };

    bool is_floating_point() const { return this->_floating_point; };

    template<typename T = float>
    static pyaf::dtype of()
    {
        std::string name = spu::runtime::type_to_string[typeid(T)].c_str();
        return pyaf::dtype(name, sizeof(T), std::is_signed<T>::value, std::is_floating_point<T>::value);
    }

    static pyaf::dtype get(const std::string& name)
    {
        if (name == spu::runtime::type_to_string[typeid(uint8_t)].c_str())
            return pyaf::dtype::of<uint8_t>();
        else if (name == spu::runtime::type_to_string[typeid(uint16_t)].c_str())
            return pyaf::dtype::of<uint16_t>();
        else if (name == spu::runtime::type_to_string[typeid(uint32_t)].c_str())
            return pyaf::dtype::of<uint32_t>();
        else if (name == spu::runtime::type_to_string[typeid(uint64_t)].c_str())
            return pyaf::dtype::of<uint64_t>();
        else if (name == spu::runtime::type_to_string[typeid(int8_t)].c_str())
            return pyaf::dtype::of<int8_t>();
        else if (name == spu::runtime::type_to_string[typeid(int16_t)].c_str())
            return pyaf::dtype::of<int16_t>();
        else if (name == spu::runtime::type_to_string[typeid(int32_t)].c_str())
            return pyaf::dtype::of<int32_t>();
        else if (name == spu::runtime::type_to_string[typeid(int64_t)].c_str())
            return pyaf::dtype::of<int64_t>();
        else if (name == spu::runtime::type_to_string[typeid(float)].c_str())
            return pyaf::dtype::of<float>();
        else if (name == spu::runtime::type_to_string[typeid(double)].c_str())
            return pyaf::dtype::of<double>();
        else
        {
            std::stringstream message;
            message << "Unknown data type '" << name << "'.";
            throw std::runtime_error(message.str());
        }
    }
};

namespace wrapper
{
inline void
wrap_generic_dtype(py::module_& m)
{
    py::class_<pyaf::dtype>(m,
                            "dtype",
                            py::dynamic_attr(),
                            R"mydelimiter(
StreamPU abstract class for data type object.)mydelimiter")
      .def_property_readonly("name", &pyaf::dtype::get_name, "dtype's name")
      .def_property_readonly(
        "is_signed", &pyaf::dtype::is_signed, "True if dtype names a signed type, False otherwise.")
      .def_property_readonly("is_floating_point",
                             &pyaf::dtype::is_floating_point,
                             "True if dtype names a floating point type, False otherwise.")
      .def_property_readonly("size", &pyaf::dtype::get_size, "Byte size of the dtype.")
      .def_property_readonly(
        "numpy",
        [](const pyaf::dtype& slf)
        { return py::module_::import("numpy").attr("dtype")(slf.get_name().c_str()).attr("type"); },
        "Get the corresponding numpy dtype.")
      .def_static("of", &pyaf::dtype::get, "name"_a, "Dtype factory.")
      .def("__repr__", [](const pyaf::dtype& slf) { return "spu." + slf.get_name(); })
      .def("__str__", [](const pyaf::dtype& slf) { return slf.get_name(); })
      .doc();
}

inline void
wrap_dtypes(py::module_& m)
{
    wrap_generic_dtype(m);
    using full_lT = tl::type_list<ALL_DTYPES>;
    full_lT::for_each(
      [&](auto t)
      {
          using T = typename decltype(t)::type;
          m.attr(spu::runtime::type_to_string[typeid(T)].c_str()) = py::cast(pyaf::dtype::of<T>());
      });
}
} // namespace wrapper
}; // namespace pyaf

#endif