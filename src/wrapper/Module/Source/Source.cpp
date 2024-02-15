#include "wrapper/Module/Source/Source.hpp"
#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_list.hpp"

#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include "wrapper/Common/Tools/type_functions.h"

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_source(py::handle scope)
{	using lB = tl::type_list<ALL_DTYPES>;
	lB::for_each([&](auto b){
		using B = typename decltype(b)::type;
		std::string B_str = aff3ct::runtime::type_to_string[typeid(B)];
		auto source_class = py::class_<aff3ct::module::Source<B>,
	                                   aff3ct::module::Module,
	                                   aff3ct::tools::Interface_set_seed,
	                                   aff3ct::tools::Interface_is_done,
	                                   aff3ct::tools::Interface_reset>(scope, std::string("Source_" + B_str).c_str());
		source_class.def(py::init<const int>(), "max_data_size"_a, py::return_value_policy::take_ownership);
	});
}
