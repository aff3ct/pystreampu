#include "wrapper/Module/Sink/NO/Sink_NO.hpp"
#include "wrapper/Common/Tools/Type/Type.hpp"

#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_sink_no(py::handle scope)
{
	using lB = tl::type_list<ALL_DTYPES>;
	lB::for_each([&](auto b){
		using B = typename decltype(b)::type;
		std::string B_str = aff3ct::runtime::type_to_string[typeid(B)];
		auto sink_class = py::class_<aff3ct::module::Sink_NO<B>, aff3ct::module::Sink<B>>(scope, std::string("Sink_NO_" + B_str).c_str());
		sink_class.def(py::init<const int>(),"max_data_size"_a, py::return_value_policy::take_ownership);
	});
}
