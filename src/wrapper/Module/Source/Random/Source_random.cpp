#include "wrapper/Module/Source/Random/Source_random.hpp"
#include "wrapper/Common/Tools/Type/Type.hpp"

#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_source_random(py::handle scope)
{
	using lB = tl::type_list<ALL_DTYPES>;
	lB::for_each([&](auto b){
		using B = typename decltype(b)::type;
		std::string B_str = aff3ct::runtime::type_to_string[typeid(B)];
		auto source_class = py::class_<aff3ct::module::Source_random<B>, aff3ct::module::Source<B>>(scope, std::string("Source_random_" + B_str).c_str());
		source_class.def(py::init<const int, const int>(),"max_data_size"_a, "seed"_a = 0, py::return_value_policy::take_ownership);
	});
}
