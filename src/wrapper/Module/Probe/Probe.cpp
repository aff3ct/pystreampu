#include "wrapper/Module/Probe/Probe.hpp"

#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_list.hpp"
#include "wrapper/Common/Tools/type_functions.h"

#include "wrapper/Module/Probe/Latency/Probe_latency.hpp"
#include "wrapper/Module/Probe/Occurrence/Probe_occurrence.hpp"
#include "wrapper/Module/Probe/Throughput/Probe_throughput.hpp"
#include "wrapper/Module/Probe/Time/Probe_time.hpp"
#include "wrapper/Module/Probe/Timestamp/Probe_timestamp.hpp"

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_probe(py::handle scope)
{
	// AProbe has a protected destructor
	py::class_<aff3ct::module::AProbe, aff3ct::module::Module, std::unique_ptr<aff3ct::module::AProbe, py::nodelete>>(scope, "AProbe");

	using lT = tl::type_list<ALL_DTYPES>;
	lT::for_each([&](auto t){
		using T = typename decltype(t)::type;
		std::string T_str = aff3ct::runtime::type_to_string[typeid(T)];
		auto probe_class = py::class_<aff3ct::module::Probe<T>,
									  aff3ct::module::AProbe,
									  aff3ct::tools::Interface_reset,
									  pyaf::wrapper::py_Probe<T>>(scope, std::string("Probe_" + T_str).c_str());
		probe_class.def(py::init<const int, const std::string &, aff3ct::tools::Reporter_probe&, const int>(), "size"_a, "col_name"_a, "reporter"_a, "n_frames"_a=1, py::return_value_policy::take_ownership);
		probe_class.def_property_readonly("datatype", &aff3ct::module::Probe<T>::get_datatype);

		py::class_<aff3ct::module::Probe_value<T>, aff3ct::module::Probe<T>>(scope, std::string("Probe_value_" + T_str).c_str())
			.def(py::init<const int, const std::string &, aff3ct::tools::Reporter_probe&, const int>(), "size"_a, "col_name"_a, "reporter"_a, "n_frames"_a=1, py::return_value_policy::take_ownership);
	});

	pyaf::wrapper::wrap_probe_latency   (scope);
	pyaf::wrapper::wrap_probe_occurrence(scope);
	pyaf::wrapper::wrap_probe_throughput(scope);
	pyaf::wrapper::wrap_probe_time      (scope);
	pyaf::wrapper::wrap_probe_timestamp (scope);
}
