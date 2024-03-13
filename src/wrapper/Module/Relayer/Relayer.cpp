#include "wrapper/Module/Relayer/Relayer.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_relayer(py::handle scope)
{
 	using int_lT = tl::type_list<ALL_DTYPES>;
	int_lT::for_each([&](auto t)
	{
		using T = typename decltype(t)::type;
		std::string T_str = aff3ct::runtime::type_to_string[typeid(T)];
		pyaf::wrapper::wrap_relayer_internal<T>(scope, "Relayer_" + T_str);
	});
}