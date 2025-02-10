#ifndef WRAPPER_STATEFUL_HPP_
#define WRAPPER_STATEFUL_HPP_

#include "wrapper/Common/pybind11_common.h"
#include <streampu.hpp>

namespace py = pybind11;

namespace spu
{
namespace module
{
class Stateful_Publicist : public Stateful
{
  public:
    using Stateful::Stateful;
    Stateful_Publicist(const Stateful& m)
      : Stateful(m) {};
    using Stateful::create_codelet;
    using Stateful::create_socket_fwd;
    using Stateful::create_socket_in;
    using Stateful::create_socket_out;
    using Stateful::create_task;
    using Stateful::deep_copy;
    using Stateful::set_n_frames_per_wave;

    virtual ~Stateful_Publicist() = default;
};
} // namespace module
} // namespace spu

namespace pyspu
{
namespace wrapper
{
void
wrap_stateful(py::handle scop);
}
} // namespace pyspu
#endif // WRAPPER_STATEFUL_HPP_
