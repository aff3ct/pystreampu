#include "wrapper/Runtime/Pipeline/Pipeline.hpp"

#include "wrapper/Common/pystreambuf.h"

#include <pybind11/functional.h>
#include <pybind11/iostream.h>
#include <pybind11/stl.h>

#include <functional>
#include <chrono>
#include <iostream>

#include <aff3ct-core.hpp>

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_pipeline(py::handle scope)
{
	auto pipeline_class = py::class_<aff3ct::runtime::Pipeline,
	                                 aff3ct::tools::Interface_get_set_n_frames>(scope, "Pipeline");
	pipeline_class.def(py::init<
	                   const std::vector<aff3ct::runtime::Task*> &,
	                   const std::vector<aff3ct::runtime::Task*> &,
	                   const std::vector<std::tuple<std::vector<aff3ct::runtime::Task*>,
					                                std::vector<aff3ct::runtime::Task*>,
													std::vector<aff3ct::runtime::Task*>>> &,
	                   const std::vector<size_t>,
	                   const std::vector<size_t>,
	                   const std::vector<bool>,
	                   const std::vector<bool>,
	                   const std::vector<std::vector<size_t>> >(),
	                   "firsts"_a,
	                   "lasts"_a,
	                   "sep_stages"_a             = std::vector<std::tuple<std::vector<aff3ct::runtime::Task*>,
					                                                       std::vector<aff3ct::runtime::Task*>,
																		   std::vector<aff3ct::runtime::Task*>>>(),
	                   "n_threads"_a              = std::vector<size_t>(),
	                   "synchro_buffer_sizes"_a   = std::vector<size_t>(),
	                   "synchro_active_waiting"_a = std::vector<bool>(),
	                   "thread_pinning"_a         = std::vector<bool>(),
	                   "puids"_a                  = std::vector<std::vector<size_t>>(),
					   py::return_value_policy::take_ownership
			);

	pipeline_class.def("exec", [](aff3ct::runtime::Pipeline& self)
	{
		py::gil_scoped_release release{};
		self.exec();
	});

	pipeline_class.def("export_dot", [](aff3ct::runtime::Pipeline& self, const std::string& file_name){
		std::ofstream f(file_name);
		self.export_dot(f);
	});

	pipeline_class.def("get_tasks_per_types", &aff3ct::runtime::Pipeline::get_tasks_per_types);
	pipeline_class.def("show_stats", [](aff3ct::runtime::Pipeline& self)
	{
		py::scoped_ostream_redirect stream(
			std::cout,                               // std::ostream&
			py::module_::import("sys").attr("stdout") // Python output
		);
	auto stages = self.get_stages();
	for (size_t s = 0; s < stages.size(); s++)
	{
		const int n_threads = stages[s]->get_n_threads();
		std::cout << "#" << std::endl << "# Pipeline stage " << s << " (" << n_threads << " thread(s)): " << std::endl;
		aff3ct::tools::Stats::show(stages[s]->get_tasks_per_types(), true);
	}
	});
};