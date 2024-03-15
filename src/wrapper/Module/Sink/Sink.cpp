#include "wrapper/Module/Sink/Sink.hpp"
#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_list.hpp"

#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include "wrapper/Common/Tools/type_functions.h"

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_sink(py::handle scope)
{	using lB = tl::type_list<ALL_DTYPES>;
	lB::for_each([&](auto b){
		using B = typename decltype(b)::type;
		std::string B_str = aff3ct::runtime::type_to_string[typeid(B)];
		auto sink_class = py::class_<aff3ct::module::Sink<B>,
	                                 aff3ct::module::Module,
	                                 aff3ct::tools::Interface_reset>(scope, std::string("Sink_" + B_str).c_str());
		sink_class.def(py::init<const int>(), "max_data_size"_a, py::return_value_policy::take_ownership);
	});
}

#include "wrapper/Module/Sink/User/Sink_user_binary.hpp"
#include "wrapper/Module/Sink/NO/Sink_NO.hpp"
void pyaf::wrapper::wrap_sinks(py::handle scope)
{
	pyaf::wrapper::wrap_sink            (scope);
	pyaf::wrapper::wrap_sink_user_binary(scope);
	pyaf::wrapper::wrap_sink_no         (scope);
}