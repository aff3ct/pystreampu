#ifndef WRAPPER_UNARYOP_HXX_
#define WRAPPER_UNARYOP_HXX_

#include "wrapper/Module/Unaryop/Unaryop.hpp"
#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace aff3ct;
using namespace aff3ct::module;

#define UOP_WRAP(name,types)\
 	using int_lT = tl::type_list<types>;\
	int_lT::for_each([&](auto ti) {\
		using TI = typename decltype(ti)::type;\
		std::string TI_str = aff3ct::runtime::type_to_string[typeid(TI)];\
		int_lT::for_each([&](auto to) {\
			using TO = typename decltype(to)::type;\
			std::string TO_str = aff3ct::runtime::type_to_string[typeid(TO)];\
			pyaf::wrapper::internal_wrap_unaryop<TI,TO,aff3ct::tools::uop_##name<TI,TO>>(scope, "Unaryop_" + std::string(#name) + "_" + TI_str + "_" + TO_str);\
		});\
	});

namespace pyaf
{
namespace wrapper
{

template <typename TI, typename TO, tools::proto_uop< TI, TO > UOP>
void internal_wrap_unaryop(py::handle scope, const std::string& name)
{
    auto doc_str = R"pbdoc()pbdoc";
    auto py_uop_class = py::class_<aff3ct::module::Unaryop<TI,TO,UOP>, aff3ct::module::Module>(scope, name.c_str());
    py_uop_class.def(py::init<const size_t>(),"n_elmts"_a, doc_str, py::return_value_policy::take_ownership);
}

void wrap_unaryop(py::handle scope)
{
	pyaf::wrapper::wrap_unaryop_abs    (scope);
	pyaf::wrapper::wrap_unaryop_not    (scope);
	//pyaf::wrapper::wrap_unaryop_not_abs(scope);
	pyaf::wrapper::wrap_unaryop_sign   (scope);
	pyaf::wrapper::wrap_unaryop_neg    (scope);
	pyaf::wrapper::wrap_unaryop_cast   (scope);
}

}
}

#endif //WRAPPER_UNARYOP_HXX_