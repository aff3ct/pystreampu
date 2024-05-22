/*#include "Socket.hpp"
#include "wrapper/Common/Tools/type_functions.h"

using namespace spu::runtime;

namespace pyaf
{
namespace wrapper
{
	template <typename TI, typename TO, spu::tools::proto_bop<TI,TO> BOP>
	py::object bop_wrapping(spu::runtime::Socket& self, spu::runtime::Socket& other){
		auto binary_op = new spu::module::Binaryop<TI,TO,BOP>(self.get_n_elmts());
		(*binary_op)[spu::module::bop::sck::perform::in1].bind(self);
		(*binary_op)[spu::module::bop::sck::perform::in2].bind(other);
		(*binary_op)[spu::module::bop::tsk::perform].exec();
		auto py_out_sck = py::cast(&(*binary_op)[spu::module::bop::sck::perform::out]);
		py_out_sck.attr("__held_mdl__") = py::cast(std::unique_ptr<spu::module::Binaryop<TI,TO,BOP>>(std::move(binary_op)));
		return py_out_sck;
	}


	#define BINARY_OPERATOR_FULL(BOP)                                                                  \
	[](spu::runtime::Socket& self, spu::runtime::Socket& other){                                   \
		if (spu::runtime::type_to_string[self.get_datatype()] == "int8"   )                          \
			return Wrapper_Socket::bop_wrapping<int8_t,  int8_t,  BOP<int8_t,  int8_t >>(self, other); \
		else if (spu::runtime::type_to_string[self.get_datatype()] == "int16"  )                     \
			return Wrapper_Socket::bop_wrapping<int16_t, int16_t, BOP<int16_t, int16_t>>(self, other); \
		else if (spu::runtime::type_to_string[self.get_datatype()] == "int32"  )                     \
			return Wrapper_Socket::bop_wrapping<int32_t, int32_t, BOP<int32_t, int32_t>>(self, other); \
		else if (spu::runtime::type_to_string[self.get_datatype()] == "int64"  )                     \
			return Wrapper_Socket::bop_wrapping<int64_t, int64_t, BOP<int64_t, int64_t>>(self, other); \
		else if (spu::runtime::type_to_string[self.get_datatype()] == "float32")                     \
			return Wrapper_Socket::bop_wrapping<float,   float,   BOP<float,   float  >>(self, other); \
		else if (spu::runtime::type_to_string[self.get_datatype()] == "float64")                     \
			return Wrapper_Socket::bop_wrapping<double,  double,  BOP<double,  double >>(self, other); \
		else                                                                                           \
		{                                                                                              \
			std::cout << "Error : type '" << spu::runtime::type_to_string[self.get_datatype()];      \
			std::cout << "' is not handled for this binary operator" << std::endl;                     \
			return py::reinterpret_borrow<object>(Py_NotImplemented);                                  \
		}                                                                                              \
	}

	#define BINARY_OPERATOR_INT(BOP)                                                                   \
	[](spu::runtime::Socket& self, spu::runtime::Socket& other){                                   \
		if (spu::runtime::type_to_string[self.get_datatype()] == "int8"   )                          \
			return Wrapper_Socket::bop_wrapping<int8_t,  int8_t,  BOP<int8_t,  int8_t >>(self, other); \
		else if (spu::runtime::type_to_string[self.get_datatype()] == "int16"  )                     \
			return Wrapper_Socket::bop_wrapping<int16_t, int16_t, BOP<int16_t, int16_t>>(self, other); \
		else if (spu::runtime::type_to_string[self.get_datatype()] == "int32"  )                     \
			return Wrapper_Socket::bop_wrapping<int32_t, int32_t, BOP<int32_t, int32_t>>(self, other); \
		else if (spu::runtime::type_to_string[self.get_datatype()] == "int64"  )                     \
			return Wrapper_Socket::bop_wrapping<int64_t, int64_t, BOP<int64_t, int64_t>>(self, other); \
		else                                                                                           \
		{                                                                                              \
			std::cout << "Error : type '" << spu::runtime::type_to_string[self.get_datatype()];      \
			std::cout << "' is not handled for this binary operator" << std::endl;                     \
			return py::reinterpret_borrow<object>(Py_NotImplemented);                                  \
		}                                                                                              \
	}
}
}*/