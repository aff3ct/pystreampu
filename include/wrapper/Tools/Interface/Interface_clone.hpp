#ifndef WRAPPER_INTERFACE_CLONE_HPP__
#define WRAPPER_INTERFACE_CLONE_HPP__

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyaf {
namespace wrapper {
class py_Interface_clone : public spu::tools::Interface_clone {
public:
  /* Trampoline (need one for each virtual function) */
  spu::tools::Interface_clone *clone() const override {
    PYBIND11_OVERRIDE_PURE(
        spu::tools::Interface_clone *, /* Return type */
        spu::tools::Interface_clone,   /* Parent class */
        clone /* Name of function in C++ (must match Python name) */
    );
  }
};

void wrap_interface_clone(py::module_ &scope);
} // namespace wrapper
} // namespace pyaf

#endif // WRAPPER_INTERFACE_CLONE_HPP__