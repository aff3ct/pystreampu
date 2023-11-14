#ifndef BIND_MODULE_HPP_
#define BIND_MODULE_HPP_

#include <pybind11/pybind11.h>
#include <string>
#include <aff3ct-core.hpp>
#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;
namespace aff3ct
{
namespace module
{
class Module_Publicist : public Module
{
	public:
	using Module::Module;
	using Module::create_codelet;
	using Module::deep_copy;
	using Module::set_doc;
	using Module::create_task;
	using Module::create_socket_in;
	using Module::create_socket_out;
	using Module::create_socket_fwd;

	virtual ~Module_Publicist() = default;
};
}
}

namespace pyaf
{
namespace wrapper
{
class Wrapper_Module : public Wrapper_py,
                       public py::class_<aff3ct::module::Module, aff3ct::module::Module_Publicist, aff3ct::tools::Interface_clone, aff3ct::tools::Interface_get_set_n_frames>
{
	public:
	Wrapper_Module(py::handle scope);
	virtual void definitions();
	virtual ~Wrapper_Module() = default;
};
}
}

#endif //BIND_MODULE_HPP_