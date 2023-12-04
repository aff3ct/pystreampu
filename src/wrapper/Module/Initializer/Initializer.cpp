#include "wrapper/Module/Initializer/Initializer.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_initializer(py::handle scope)
{
 	using int_lT = tl::type_list<ALL_DTYPES>;
	int_lT::for_each([&](auto t)
	{
		using T = typename decltype(t)::type;
		std::string T_str = aff3ct::runtime::type_to_string[typeid(T)];
		pyaf::wrapper::wrap_initializer_internal<T>(scope, "Initializer_" + T_str);
	});
}