#ifndef WRAPPER_INTERFACE_SET_SEED_HPP__
#define WRAPPER_INTERFACE_SET_SEED_HPP__

#include "wrapper/Common/pybind11_common.h"
#include <streampu.hpp>

namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
class py_Interface_set_seed : public spu::tools::Interface_set_seed
{
  public:
    /* Trampoline (need one for each virtual function) */
    void set_seed(const int seed) override
    {
        PYBIND11_OVERRIDE_PURE(void,                           /* Return type */
                               spu::tools::Interface_set_seed, /* Parent class */
                               set_seed,                       /* Name of function in C++ (must match Python name) */
                               seed);
    }
};

void
wrap_interface_set_seed(py::module_& scope);
} // namespace wrapper
} // namespace pyspu

#endif // WRAPPER_INTERFACE_SET_SEED_HPP__