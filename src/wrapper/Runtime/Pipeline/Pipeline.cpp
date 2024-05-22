#include "wrapper/Runtime/Pipeline/Pipeline.hpp"

#include "wrapper/Common/pystreambuf.h"

#include <pybind11/functional.h>
#include <pybind11/iostream.h>
#include <pybind11/stl.h>

#include <functional>
#include <chrono>
#include <iostream>

#include <streampu.hpp>

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_pipeline(py::handle scope)
{
	auto pipeline_class = py::class_<spu::runtime::Pipeline,
	                                 spu::tools::Interface_get_set_n_frames>(scope, "_Pipeline");
	pipeline_class.def(py::init([](const std::vector<spu::runtime::Task*> &firsts,
	                               const std::vector<spu::runtime::Task*> &lasts,
	                               const std::vector<std::tuple<std::vector<spu::runtime::Task*>,
	                                                            std::vector<spu::runtime::Task*>,
	                                                            std::vector<spu::runtime::Task*>>> &sep_stages,
	                               const std::vector<size_t> n_threads,
	                               const std::vector<size_t> synchro_buffer_sizes,
	                               const std::vector<bool> synchro_active_waiting,
	                               const std::vector<bool> thread_pinning,
	                               const std::vector<std::vector<size_t>> puids)
	                               {
	                                	return std::unique_ptr<spu::runtime::Pipeline>(new spu::runtime::Pipeline(firsts, lasts, sep_stages, n_threads, synchro_buffer_sizes, synchro_active_waiting, thread_pinning, puids));
								   }),
	                   "firsts"_a,
	                   "lasts"_a,
	                   "sep_stages"_a             = std::vector<std::tuple<std::vector<spu::runtime::Task*>,
					                                                       std::vector<spu::runtime::Task*>,
																		   std::vector<spu::runtime::Task*>>>(),
	                   "n_threads"_a              = std::vector<size_t>(),
	                   "synchro_buffer_sizes"_a   = std::vector<size_t>(),
	                   "synchro_active_waiting"_a = std::vector<bool>(),
	                   "thread_pinning"_a         = std::vector<bool>(),
	                   "puids"_a                  = std::vector<std::vector<size_t>>(),
					   py::return_value_policy::take_ownership
			);
	pipeline_class.def("get_original_modules", &spu::runtime::Pipeline::get_original_modules);

	pipeline_class.def("exec", [](spu::runtime::Pipeline& self)
	{
		py::gil_scoped_release release{};
		self.exec();
	});

	pipeline_class.def("export_dot", [](spu::runtime::Pipeline& self, const std::string& file_name){
		std::ofstream f(file_name);
		self.export_dot(f);
	});

	pipeline_class.def("get_modules_per_threads", &spu::runtime::Pipeline::get_modules_per_threads);
	pipeline_class.def("get_modules_per_types",   &spu::runtime::Pipeline::get_modules_per_types  );
	pipeline_class.def("get_tasks_per_types",     &spu::runtime::Pipeline::get_tasks_per_types    );
	pipeline_class.def("get_tasks_per_threads",   &spu::runtime::Pipeline::get_tasks_per_threads  );
	pipeline_class.def("__getitem__",             &spu::runtime::Pipeline::operator[]             , py::is_operator());
	pipeline_class.def("bind_adaptors",           &spu::runtime::Pipeline::bind_adaptors          );
	pipeline_class.def("unbind_adaptors",         &spu::runtime::Pipeline::unbind_adaptors        );
	pipeline_class.def("is_bound_adaptors",       &spu::runtime::Pipeline::is_bound_adaptors      );

	pipeline_class.def("show_stats", [](spu::runtime::Pipeline& self)
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
		spu::tools::Stats::show(stages[s]->get_tasks_per_types(), true);
	}
	});
	pipeline_class.def_property_readonly("stages",      &spu::runtime::Pipeline::get_stages,       py::return_value_policy::reference);
	pipeline_class.def_property_readonly("last_tasks",  &spu::runtime::Pipeline::get_lasts_tasks,  py::return_value_policy::reference);
	pipeline_class.def_property_readonly("first_tasks", &spu::runtime::Pipeline::get_firsts_tasks, py::return_value_policy::reference);
	pipeline_class.def_property("auto_stop", &spu::runtime::Pipeline::is_auto_stop, &spu::runtime::Pipeline::set_auto_stop);

}