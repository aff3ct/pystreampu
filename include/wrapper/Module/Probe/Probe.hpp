#ifndef WRAPPER_PROBE_HPP_
#define WRAPPER_PROBE_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
// std::type_index get_datatype() const = 0;
template<typename T = uint8_t>
class py_Probe : spu::module::Probe<T>
{
  public:
    using spu::module::Probe<T>::Probe;

    void register_reporter(spu::tools::Reporter_probe* reporter) override
    {
        PYBIND11_OVERRIDE_PURE(void,                  /* Return type */
                               spu::module::Probe<T>, /* Parent class */
                               register_reporter,     /* Name of function in C++ (must
                                                         match Python name) */
                               reporter               /* Argument(s) (...) */
        );
    }
};

void
wrap_probe(py::handle scope);
} // namespace wrapper
} // namespace pyaf

#endif // WRAPPER_PROBE_HPP_