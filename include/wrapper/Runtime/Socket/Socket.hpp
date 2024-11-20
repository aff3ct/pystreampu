#ifndef BIND_SOCKET_HPP_
#define BIND_SOCKET_HPP_

#include "wrapper/Common/pybind11_common.h"

#include <streampu.hpp>

namespace py = pybind11;

namespace spu
{
namespace runtime
{
class Socket_Publicist : public Socket
{
  public:
    virtual ~Socket_Publicist() = default;
};
} // namespace runtime
} // namespace spu

namespace pyspu
{
namespace wrapper
{
void wrap_socket(py::handle scope);
} // namespace wrapper
} // namespace pyspu

#endif // BIND_SOCKET_HPP_