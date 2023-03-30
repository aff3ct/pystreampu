#ifndef Wrapper_Array_HPP_
#define Wrapper_Array_HPP_

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>

#include <aff3ct-core.hpp>
#include <vector>
#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"

using namespace aff3ct::module;
namespace py = pybind11;

namespace aff3ct
{

namespace module
{

template <typename T>
class Array : public Module
{
private:
	std::vector<T> data;

public:

	Array(const std::vector<T>& vec);
	Array(const int sz, const T val = (T)0);
	virtual ~Array() = default;
	virtual Array* clone() const;
};

}
}

namespace pyaf
{
namespace wrapper
{
	void wrap_array(py::module_ &scope);
}
}

#endif //Wrapper_Array_HPP_