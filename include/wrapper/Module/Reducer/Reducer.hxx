#ifndef WRAPPER_REDUCER_HXX_
#define WRAPPER_REDUCER_HXX_

#include "wrapper/Module/Reducer/Reducer.hpp"
#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace aff3ct;
using namespace aff3ct::module;

#define RED_WRAP(name, TIlist, TOlist)\
 	using lTI = tl::type_list<TIlist>;\
	using lTO = tl::type_list<TOlist>;\
	lTI::for_each([&](auto ti) {\
		using TI = typename decltype(ti)::type;\
		std::string TI_str = aff3ct::runtime::type_to_string[typeid(TI)];\
		lTO::for_each([&](auto to) {\
			using TO = typename decltype(to)::type;\
			std::string TO_str = aff3ct::runtime::type_to_string[typeid(TO)];\
			pyaf::wrapper::internal_wrap_reducer<TI,TO,aff3ct::tools::bop_##name<TI,TO>>(scope, "Reducer_" + std::string(#name) + "_" + TI_str + "_" + TO_str);\
		});\
	});

namespace pyaf
{
namespace wrapper
{

template <typename TI, typename TO, tools::proto_bop< TI, TO > BOP>
void internal_wrap_reducer(py::handle scope, const std::string& name)
{
    auto doc_str = R"pbdoc()pbdoc";
    auto py_red_class = py::class_<aff3ct::module::Reducer<TI,TO,BOP>, aff3ct::module::Module>(scope, name.c_str());
    py_red_class.def(py::init<const size_t>(),"n_elmts"_a, doc_str, py::return_value_policy::take_ownership);
}

void wrap_reducer(py::handle scope)
{
	pyaf::wrapper::wrap_reducer_add(scope);
	pyaf::wrapper::wrap_reducer_sub(scope);
	pyaf::wrapper::wrap_reducer_mul(scope);
	pyaf::wrapper::wrap_reducer_div(scope);
	pyaf::wrapper::wrap_reducer_min(scope);
	pyaf::wrapper::wrap_reducer_max(scope);
	pyaf::wrapper::wrap_reducer_le (scope);
	pyaf::wrapper::wrap_reducer_lt (scope);
	pyaf::wrapper::wrap_reducer_ge (scope);
	pyaf::wrapper::wrap_reducer_gt (scope);
	pyaf::wrapper::wrap_reducer_ne (scope);
	pyaf::wrapper::wrap_reducer_eq (scope);

	pyaf::wrapper::wrap_reducer_and(scope);
	pyaf::wrapper::wrap_reducer_or (scope);
	pyaf::wrapper::wrap_reducer_xor(scope);
}

}
}

#endif //WRAPPER_REDUCER_HXX_