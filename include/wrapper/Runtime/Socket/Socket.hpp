#ifndef BIND_SOCKET_HPP_
#define BIND_SOCKET_HPP_

#include <pybind11/pybind11.h>
#include <streampu.hpp>

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;

namespace spu {
namespace runtime {
class Socket_Publicist : public Socket {
public:
  virtual ~Socket_Publicist() = default;
};
} // namespace runtime
} // namespace spu

namespace pyaf {
namespace wrapper {
/*class Wrapper_Socket : public Wrapper_py,
                       public py::class_<spu::runtime::Socket,
spu::tools::Interface_reset, std::shared_ptr<spu::runtime::Socket>>//,
spu::tools::Interface_reset
{
        protected:
        template <typename TI, typename TO, spu::tools::proto_bop<TI,TO> BOP>
        static py::object bop_wrapping(spu::runtime::Socket& self,
spu::runtime::Socket& other);

        public:
        Wrapper_Socket(py::handle scope);
        virtual void definitions();
        virtual ~Wrapper_Socket() = default;
};*/
// py::object bop_wrapping(spu::runtime::Socket& self, spu::runtime::Socket&
// other);
void wrap_socket(py::handle scope);
} // namespace wrapper
} // namespace pyaf

/*#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "Socket.hxx"
#endif*/
#endif // BIND_SOCKET_HPP_