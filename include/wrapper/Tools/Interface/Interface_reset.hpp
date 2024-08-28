/*!
 * \file
 * \brief Class tools::Interface_get_set_n_frames.
 */
#ifndef WRAPPER_INTERFACE_RESET_HPP__
#define WRAPPER_INTERFACE_RESET_HPP__

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
class py_Interface_reset : public spu::tools::Interface_reset
{
  public:
    /* Trampoline (need one for each virtual function) */
    void reset() override
    {
        PYBIND11_OVERRIDE_PURE(void,                        /* Return type */
                               spu::tools::Interface_reset, /* Parent class */
                               reset                        /* Name of function in C++ (must match Python name) */
        );
    };
};

void
wrap_interface_reset(py::module_& scope);
} // namespace wrapper
} // namespace pyspu

#endif // WRAPPER_INTERFACE_RESET_HPP__