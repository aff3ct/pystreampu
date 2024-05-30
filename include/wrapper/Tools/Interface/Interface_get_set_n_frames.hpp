/*!
 * \file
 * \brief Class tools::Interface_get_set_n_frames.
 */
#ifndef WRAPPER_INTERFACE_GET_SET_N_FRAMES_HPP__
#define WRAPPER_INTERFACE_GET_SET_N_FRAMES_HPP__

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
class py_Interface_get_set_n_frames : public spu::tools::Interface_get_set_n_frames
{
  public:
    /* Trampoline (need one for each virtual function) */
    size_t get_n_frames() const override
    {
        PYBIND11_OVERRIDE_PURE(size_t,                                 /* Return type */
                               spu::tools::Interface_get_set_n_frames, /* Parent class */
                               get_n_frames /* Name of function in C++ (must match Python name) */
        );
    };
    void set_n_frames(const size_t n_frames) override
    {
        PYBIND11_OVERRIDE_PURE(void,                                   /* Return type */
                               spu::tools::Interface_get_set_n_frames, /* Parent class */
                               set_n_frames, /* Name of function in C++ (must match Python name) */
                               n_frames      /* Argument(s) (...)*/
        );
    };
};

void
wrap_interface_get_set_n_frames(py::module_& scope);
} // namespace wrapper
} // namespace pyaf

#endif // WRAPPER_INTERFACE_GET_SET_N_FRAMES_HPP__