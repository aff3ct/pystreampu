#ifndef WRAPPER_INTERFACE_WAITING_HPP__
#define WRAPPER_INTERFACE_WAITING_HPP__

#include "wrapper/Common/pybind11_common.h"
#include <streampu.hpp>

namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
class py_Interface_waiting : public spu::tools::Interface_waiting
{
  public:
    /* Trampoline (need one for each virtual function) */
    void send_cancel_signal() override
    {
        PYBIND11_OVERRIDE_PURE(void,                          /* Return type */
                               spu::tools::Interface_waiting, /* Parent class */
                               send_cancel_signal             /* Name of function in C++ (must
                                                                 match Python name) */
        );
    }
    void wake_up() override
    {
        PYBIND11_OVERRIDE_PURE(void,                          /* Return type */
                               spu::tools::Interface_waiting, /* Parent class */
                               wake_up                        /* Name of function in C++ (must match Python name) */
        );
    }
    void cancel_waiting() override
    {
        PYBIND11_OVERRIDE_PURE(void,                          /* Return type */
                               spu::tools::Interface_waiting, /* Parent class */
                               cancel_waiting                 /* Name of function in C++ (must match Python name) */
        );
    }
};

void
wrap_interface_waiting(py::module_& scope);
} // namespace wrapper
} // namespace pyspu

#endif // WRAPPER_INTERFACE_WAITING_HPP__