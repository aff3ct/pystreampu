#include "wrapper/Tools/Reporter/Probe/Reporter_probe.hpp"
#include "wrapper/Common/Tools/Format/Format.hpp"

#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_list.hpp"
#include "wrapper/Common/Tools/type_functions.h"

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_reporter_probe(py::module_& scope)
{
	auto rep_probe_class = py::class_<aff3ct::tools::Reporter_probe, aff3ct::tools::Reporter>(scope, "Reporter_probe");

	// Constructor
    rep_probe_class.def(py::init<const std::string&, const std::string&, const int>(), "group_name"_a, "group_description"_a, "n_frames"_a = 1);

    // Probe factory
	using lT = tl::type_list<ALL_DTYPES>;
	lT::for_each([&](auto t){
		using T = typename decltype(t)::type;
		std::string T_str = aff3ct::runtime::type_to_string[typeid(T)];
		rep_probe_class.def(std::string("_create_probe_value_" + T_str).c_str(), &aff3ct::tools::Reporter_probe::create_probe_value<T>, "name"_a, "unit"_a = "", "buffer_size"_a = 100, "socket_size"_a = 1, "format"_a = pyaf::fmtflags::scientific, "precision"_a = 3);
	});
    rep_probe_class.def("create_probe_throughput_mbps", &aff3ct::tools::Reporter_probe::create_probe_throughput_mbps, "name"_a, "data_size"_a = 1, "buffer_size"_a = 100, "format"_a = pyaf::fmtflags::dec|pyaf::fmtflags::fixed, "precision"_a = 3);
    rep_probe_class.def("create_probe_throughput",      &aff3ct::tools::Reporter_probe::create_probe_throughput,      "name"_a, "unit"_a = "", "data_size"_a=1, "factor"_a=1.,  "buffer_size"_a = 100, "format"_a = pyaf::fmtflags::dec|pyaf::fmtflags::fixed, "precision"_a = 3);
    rep_probe_class.def("create_probe_latency",         &aff3ct::tools::Reporter_probe::create_probe_latency,         "name"_a, "buffer_size"_a = 100, "format"_a = pyaf::fmtflags::scientific, "precision"_a = 3);
    rep_probe_class.def("create_probe_time",            &aff3ct::tools::Reporter_probe::create_probe_time,            "name"_a, "buffer_size"_a = 100, "format"_a = pyaf::fmtflags::scientific, "precision"_a = 2);
    rep_probe_class.def("create_probe_timestamp",       &aff3ct::tools::Reporter_probe::create_probe_timestamp,       "name"_a, "buffer_size"_a = 100, "format"_a = pyaf::fmtflags::dec|pyaf::fmtflags::fixed, "precision"_a = 2);
    rep_probe_class.def("create_probe_timestamp_mod",   &aff3ct::tools::Reporter_probe::create_probe_timestamp_mod,   "name"_a, "mod"_a, "buffer_size"_a = 100, "format"_a = pyaf::fmtflags::scientific, "precision"_a = 2);
    rep_probe_class.def("create_probe_occurrence",      &aff3ct::tools::Reporter_probe::create_probe_occurrence,      "name"_a, "buffer_size"_a = 100, "unit"_a = "", "format"_a = pyaf::fmtflags::scientific, "precision"_a = 3);
}
