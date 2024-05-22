#ifndef BIND_MODULE_HPP_
#define BIND_MODULE_HPP_

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"
#include <pybind11/pybind11.h>
#include <streampu.hpp>
#include <string>

namespace py = pybind11;
namespace spu {
namespace module {
class Module_Publicist : public Module {
public:
  using Module::Module;
  Module_Publicist(const Module &m) : Module(m) {};
  using Module::create_codelet;
  using Module::create_socket_fwd;
  using Module::create_socket_in;
  using Module::create_socket_out;
  using Module::create_task;
  using Module::deep_copy;
  using Module::set_n_frames_per_wave;

  virtual ~Module_Publicist() = default;
};
} // namespace module
} // namespace spu

namespace pyaf {
namespace wrapper {
class Wrapper_Module
    : public Wrapper_py,
      public py::class_<spu::module::Module, spu::module::Module_Publicist,
                        spu::tools::Interface_clone,
                        spu::tools::Interface_get_set_n_frames> {
public:
  Wrapper_Module(py::handle scope);
  virtual void definitions();
  virtual ~Wrapper_Module() = default;
};
} // namespace wrapper
} // namespace pyaf

#endif // BIND_MODULE_HPP_