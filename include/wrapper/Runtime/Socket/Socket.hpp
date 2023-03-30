#ifndef BIND_SOCKET_HPP_
#define BIND_SOCKET_HPP_

#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
class Wrapper_Socket : public Wrapper_py,
                       public py::class_<aff3ct::runtime::Socket, aff3ct::tools::Interface_reset, std::shared_ptr<aff3ct::runtime::Socket>>//, aff3ct::tools::Interface_reset
{
	protected:
	template <typename TI, typename TO, aff3ct::tools::proto_bop<TI,TO> BOP>
	static py::object bop_wrapping(aff3ct::runtime::Socket& self, aff3ct::runtime::Socket& other);

	public:
	Wrapper_Socket(py::handle scope);
	virtual void definitions();
	virtual ~Wrapper_Socket() = default;
};
}
}
#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "Socket.hxx"
#endif
#endif //BIND_SOCKET_HPP_