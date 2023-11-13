#include <sstream>
#include <string>
#include <memory>
#include <map>
#include <typeinfo>

#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include "wrapper/Runtime/Socket/Socket.hpp"
#include "wrapper/Common/Tools/Type/Type.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;
using namespace aff3ct::runtime;

#define BOP_RETURN_ARGS py::return_value_policy::reference, py::is_operator(), py::keep_alive<0,1>(), py::keep_alive<0,2>()

std::map<std::type_index, std::string> type_map = {{typeid(int8_t  ), py::format_descriptor<int8_t  >::format()},
                                                   {typeid(int16_t ), py::format_descriptor<int16_t >::format()},
                                                   {typeid(int32_t ), py::format_descriptor<int32_t >::format()},
                                                   {typeid(int64_t ), py::format_descriptor<int64_t >::format()},
                                                   {typeid(uint8_t ), py::format_descriptor<uint8_t >::format()},
                                                   {typeid(uint16_t), py::format_descriptor<uint16_t>::format()},
                                                   {typeid(uint32_t), py::format_descriptor<uint32_t>::format()},
                                                   {typeid(uint64_t), py::format_descriptor<uint64_t>::format()},
                                                   {typeid(float   ), py::format_descriptor<float   >::format()},
                                                   {typeid(double  ), py::format_descriptor<double  >::format()}};


void pyaf::wrapper::wrap_socket(py::handle scope)
{
	py::class_<Socket, aff3ct::tools::Interface_reset, std::shared_ptr<Socket>> py_socket(scope, "Socket", py::buffer_protocol(), py::dynamic_attr());

	py::enum_<socket_t>(py_socket, "directions", "Enumeration of socket directions")
      .value("IN",  socket_t::SIN, "Input socket")
      .value("OUT", socket_t::SOUT, "Output socket")
	  .value("FWD", socket_t::SFWD, "Forward socket");

	py_socket.def_buffer([](Socket &s) -> py::buffer_info{
	if (s.get_name() == "status")
	{
		size_t n_w = (size_t)s.get_task().get_module().get_n_waves();
		return py::buffer_info(
			s.get_dataptr(),            /* Pointer to buffer */
			s.get_datatype_size(),      /* Size of one scalar */
			type_map[s.get_datatype()], /* Python struct-style format descriptor */
			1,                          /* Number of dimensions */
			{n_w},                        /* Buffer dimensions */
			{(size_t)s.get_datatype_size()}
		);
	}
	else
	{
		size_t n_frames = s.get_task().get_module().get_n_frames();
		size_t n_row    = n_frames;
		size_t n_col    = s.get_n_elmts()/n_frames;
		if (n_row > 1)
		{
			return py::buffer_info(
				s.get_dataptr(),            /* Pointer to buffer */
				s.get_datatype_size(),      /* Size of one scalar */
				type_map[s.get_datatype()], /* Python struct-style format descriptor */
				2,                          /* Number of dimensions */
				{n_row, n_col},             /* Buffer dimensions */
				{(size_t)s.get_datatype_size()*n_col, (size_t)s.get_datatype_size()});
		}
		else
		{
			return py::buffer_info(
				s.get_dataptr(),            /* Pointer to buffer */
				s.get_datatype_size(),      /* Size of one scalar */
				type_map[s.get_datatype()], /* Python struct-style format descriptor */
				1,                          /* Number of dimensions */
				{n_col},                    /* Buffer dimensions */
				{(size_t)s.get_datatype_size()});
		}
	}
	});
	py_socket.def_property_readonly("task", &aff3ct::runtime::Socket::get_task, py::return_value_policy::reference, "Task owning the socket.");
	py_socket.def_property_readonly("n_elmts", &aff3ct::runtime::Socket::get_n_elmts, "Number of elements per `n_frames`");
	py_socket.def_property_readonly("dtype", [](const aff3ct::runtime::Socket& self){return pyaf::dtype::get(self.get_datatype_string());}, "Data type.");
	py_socket.def_property_readonly("bound_sockets", &aff3ct::runtime::Socket::get_bound_sockets, py::return_value_policy::reference, "Sockets to wich the socket is bound (for output sockets only).");
	py_socket.def_property_readonly("bound_socket", static_cast<Socket&(Socket::*)()>(&aff3ct::runtime::Socket::get_bound_socket), py::keep_alive<0, 1>(), "Socket bound to self (for input sockets only).");

	py_socket.def("has_data", [](const aff3ct::runtime::Socket& self)
	{
		return self.get_dataptr() != nullptr;
	}, "Return True if the socket has data allocated.");
	py_socket.def_property_readonly("dataaddr", [](const aff3ct::runtime::Socket& self){
		std::stringstream ss;
		ss << self.get_dataptr();
		return ss.str();
	}, "Return the socket data address as str.");

	py_socket.def_property_readonly("numpy", [](aff3ct::runtime::Socket& self)
	{
		py::array array = py::cast(self);
		return array;
	},
	"Numpy array view of the socket (copy-less).");
	/*py_socket.def("__getitem__", [](aff3ct::runtime::Socket& sckt, py::handle& index) {
		py::array array = py::cast(sckt);
		return array.attr("__getitem__")(index);
		},py::return_value_policy::reference);

	py_socket.def("__setitem__", [](aff3ct::runtime::Socket& sckt, py::handle& index, py::handle& value) {
		py::array arr = py::cast(sckt);
		arr.attr("__setitem__")(index, value);
		},py::return_value_policy::reference);*/

	py_socket.def("__bool__", [](const aff3ct::runtime::Socket& sckt) {
		size_t n_frames = sckt.get_task().get_module().get_n_frames();
		size_t n        = sckt.get_n_elmts()/n_frames;
		if (n > n_frames)
		{
			std::stringstream message;
			message << "The truth value of an array with more than one element is ambiguous.";
			throw std::runtime_error(message.str());
		}
		     if (sckt.get_datatype() == typeid(int8_t  )) return (bool)(static_cast<int8_t*  >(sckt.get_dataptr())[0]);
		else if (sckt.get_datatype() == typeid(int16_t )) return (bool)(static_cast<int16_t* >(sckt.get_dataptr())[0]);
		else if (sckt.get_datatype() == typeid(int32_t )) return (bool)(static_cast<int32_t* >(sckt.get_dataptr())[0]);
		else if (sckt.get_datatype() == typeid(int64_t )) return (bool)(static_cast<int64_t* >(sckt.get_dataptr())[0]);
		else if (sckt.get_datatype() == typeid(uint8_t )) return (bool)(static_cast<uint8_t* >(sckt.get_dataptr())[0]);
		else if (sckt.get_datatype() == typeid(uint16_t)) return (bool)(static_cast<uint16_t*>(sckt.get_dataptr())[0]);
		else if (sckt.get_datatype() == typeid(uint32_t)) return (bool)(static_cast<uint32_t*>(sckt.get_dataptr())[0]);
		else if (sckt.get_datatype() == typeid(uint64_t)) return (bool)(static_cast<uint64_t*>(sckt.get_dataptr())[0]);
		else if (sckt.get_datatype() == typeid(float   )) return (bool)(static_cast<float*   >(sckt.get_dataptr())[0]);
		else if (sckt.get_datatype() == typeid(double  )) return (bool)(static_cast<double*  >(sckt.get_dataptr())[0]);
		else
		{
			std::stringstream message;
			message << "Unknown socket type '" << sckt.get_datatype_string() << "'.";
			throw std::runtime_error(message.str());
		}
	});

	py_socket.def("__bind__", [](aff3ct::runtime::Socket& self, aff3ct::runtime::Socket& s_out, const int priority)
	{
		self.bind(s_out, priority);
	}, "Binds the socket to socket 's_out' with priority 'priority'.", "s_out"_a, "priority"_a=1);

	/*py_socket.def("bind", [](aff3ct::runtime::Socket& self, const float& cst)
	{
		aff3ct::module::Task&   t = self.get_task();
		if (t.get_socket_type(self) == socket_t::SOUT )
		{
			std::stringstream message;
			message << "Binding to constant is only allowed for input sockets.";
			throw std::runtime_error(message.str());
		}
		if (self.get_datatype() != typeid(float))
		{
			std::stringstream message;
			message << "Constant type and socket datatype should be identical.";
			throw std::runtime_error(message.str());
		}

		size_t n_frames = (size_t)self.get_task().get_module().get_n_frames();
		size_t n_elts   = (size_t)self.get_n_elmts()/n_frames;
		auto cst_mdl = new aff3ct::module::Source_array<float>(std::vector<float>(n_elts, cst));

		cst_mdl->set_n_frames(n_frames);
		self.reset();
		self.bind((*cst_mdl)[src::sck::generate::U_K]);
		(*cst_mdl)[src::tsk::generate].exec();
		auto self_ = py::cast(&self);
		self_.attr("__tag__") = py::cast(std::unique_ptr<aff3ct::module::Source_array<float>>(std::move(cst_mdl)));
	}
	);*/
	/*
	py_socket.def("bind", [](aff3ct::runtime::Socket& self, py::array& arr)
	{
		size_t n_row = (size_t)self.get_task().get_module().get_n_frames();
		size_t n_col = (size_t)self.get_n_elmts()/n_row;

		py::buffer_info buffer = arr.request();

		if (n_row > 1 && buffer.ndim == 2)
		{
			if ((size_t)buffer.shape[0] != n_row || (size_t)buffer.shape[1] != n_col)
			{
				std::stringstream message;
				message << "The shape of the array must match the socket one.";
				message << "Socket shape: " << n_row << " x " << n_col << ".";
				message << "Array shape: " << buffer.shape[0] << " x " << buffer.shape[1] << ".\n";
				throw std::runtime_error(message.str());
			}
		}
		else if (n_row == 1 && buffer.ndim == 1)
		{
			if ((size_t)buffer.shape[0] != n_col)
			{
				std::stringstream message;
				message << "The shape of the array must match the socket one.";
				message << "Socket shape: " << 1 << " x " << n_col << ".";
				message << "Array shape: " << 1 << " x " << buffer.shape[0] << ".\n";
				throw std::runtime_error(message.str());
			}
		}

		py::array py_self = py::cast(self);
		if (!arr.dtype().is(py_self.dtype()))
		{
			std::stringstream message;
			message << "The dtype of the array must match the socket one.\n";
			message << "Socket dtype: " << py_self.dtype().attr("name").cast<std::string>() << ".\n";
			message << "Array dtype: " << arr.dtype().attr("name").cast<std::string>() << ".\n";
			throw std::runtime_error(message.str());
		}

		self.bind(buffer.ptr);
	}, "Binds the socket to the numpy array 'array' with priority 'priority'.", "array"_a);*/
	py_socket.def_property_readonly("name", &aff3ct::runtime::Socket::get_name);
	py_socket.def_property_readonly("doc", &aff3ct::runtime::Socket::get_doc);
	py_socket.def_property_readonly("direction", [](const aff3ct::runtime::Socket& self)
	{
		aff3ct::runtime::Task&   t = self.get_task();
		return t.get_socket_type(self);
	}, "Direction of the socket ()");

};
