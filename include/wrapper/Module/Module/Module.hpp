#ifndef BIND_MODULE_HPP_
#define BIND_MODULE_HPP_

#include <pybind11/pybind11.h>
#include <string>
#include <streampu.hpp>
#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;
namespace spu
{
namespace module
{
class Module_Publicist : public Module
{
	public:
	using Module::Module;
	Module_Publicist(const Module& m) : Module(m) {};
	using Module::create_codelet;
	using Module::deep_copy;
	using Module::create_task;
	using Module::create_socket_in;
	using Module::create_socket_out;
	using Module::create_socket_fwd;
	using Module::set_n_frames_per_wave;

	virtual ~Module_Publicist() = default;
};
}
}

namespace pyaf
{
namespace wrapper
{
class Wrapper_Module : public Wrapper_py,
                       public py::class_<spu::module::Module, spu::module::Module_Publicist, spu::tools::Interface_clone, spu::tools::Interface_get_set_n_frames>
{
	public:
	Wrapper_Module(py::handle scope);
	virtual void definitions();
	virtual ~Wrapper_Module() = default;
};
}
}

#endif //BIND_MODULE_HPP_