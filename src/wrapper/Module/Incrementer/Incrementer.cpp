#include "wrapper/Module/Incrementer/Incrementer.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_incrementer(py::handle scope)
{
 	using int_lT = tl::type_list<ALL_DTYPES>;
	int_lT::for_each([&](auto t)
	{
		using T = typename decltype(t)::type;
		std::string T_str = aff3ct::runtime::type_to_string[typeid(T)];
		pyaf::wrapper::wrap_incrementer_internal<T>(scope, "Incrementer_" + T_str);
	});
}