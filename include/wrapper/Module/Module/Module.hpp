#ifndef BIND_MODULE_HPP_
#define BIND_MODULE_HPP_

#include "wrapper/Common/pybind11_common.h"
#include <streampu.hpp>
#include <string>

namespace py = pybind11;
namespace spu
{
namespace module
{
class Module_Publicist : public Module
{
  public:
    using Module::Module;
    Module_Publicist(const Module& m)
      : Module(m) {};
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

namespace pyspu
{
namespace wrapper
{
void wrap_module(py::handle scope);
} // namespace wrapper
} // namespace pyspu

#endif // BIND_MODULE_HPP_