#ifndef TYPE_FUNCTIONS_H
#define TYPE_FUNCTIONS_H

#include <typeindex>
#include <typeinfo>
#include <string>
#include <map>
#include <memory>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

#define UINT_DTYPES  uint8_t, uint16_t, uint32_t, uint64_t
#define INT_DTYPES   int8_t, int16_t, int32_t, int64_t
#define FLOAT_DTYPES float, double
#define ALL_DTYPES UINT_DTYPES, INT_DTYPES, FLOAT_DTYPES
#define ALL_INT_DTYPES UINT_DTYPES, INT_DTYPES
#define SIGNED_DTYPES INT_DTYPES, FLOAT_DTYPES

namespace pyaf
{

	/*enum type {
  	_uint8,
	_uint16,
	_uint32,
	_uint64,
	_int8,
	_int16,
	_int32,
	_int64,
  	_float,
  	_double,
	};*/

	namespace utils
	{

		std::string inline typeid2str(const std::type_index & type_id)
		{
			if      (type_id == typeid(uint8_t  ))
				return py::format_descriptor<uint8_t >::format();
			else if (type_id == typeid(uint16_t ))
				return py::format_descriptor<uint16_t >::format();
			else if (type_id == typeid(uint32_t ))
				return py::format_descriptor<uint32_t >::format();
			else if (type_id == typeid(uint64_t ))
				return py::format_descriptor<uint64_t >::format();
			else if (type_id == typeid(int8_t  ))
				return py::format_descriptor<int8_t >::format();
			else if (type_id == typeid(int16_t ))
				return py::format_descriptor<int16_t >::format();
			else if (type_id == typeid(int32_t ))
				return py::format_descriptor<int32_t >::format();
			else if (type_id == typeid(int64_t ))
				return py::format_descriptor<int64_t >::format();
			else if (type_id == typeid(float   ))
				return py::format_descriptor<float   >::format();
			else if (type_id == typeid(double  ))
				return py::format_descriptor<double >::format();
			else
			{
				std::stringstream message;
				message << "Type '" << type_id.name() << "' is not supported. Allowed types are 'int8', 'int16', 'int32', 'int64', 'float32', and 'double'.";
				throw std::runtime_error(message.str());
			}
		}

		std::type_index inline str2typeid(const std::string & type_str)
		{
			if      (type_str == "uint8")
				return typeid(uint8_t );
			else if (type_str == "uint16")
				return typeid(uint16_t );
			else if (type_str == "uint32")
				return typeid(uint32_t );
			else if (type_str == "uint64")
				return typeid(uint64_t );
			else if (type_str == "int8")
				return typeid(int8_t );
			else if (type_str == "int16")
				return typeid(int16_t );
			else if (type_str == "int32")
				return typeid(int32_t );
			else if (type_str == "int64")
				return typeid(int64_t );
			else if (type_str == "float32")
				return typeid(float);
			else if (type_str == "float64")
				return typeid(double);
			else
			{
				std::stringstream message;
				message << "Type '" << type_str << "' is not supported. Allowed types are 'int8', 'int16', 'int32', 'int64', 'float32', and 'double'.";
				throw std::runtime_error(message.str());
			}
		}
	}
}

#endif