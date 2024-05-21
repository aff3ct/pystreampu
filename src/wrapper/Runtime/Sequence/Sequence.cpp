#include "wrapper/Runtime/Sequence/Sequence.hpp"

#include "wrapper/Common/pystreambuf.h"

#include <pybind11/functional.h>
#include <pybind11/iostream.h>
#include <pybind11/stl.h>

#include <functional>
#include <atomic>
#include <chrono>
#include <iostream>

#include <aff3ct-core.hpp>

namespace py = pybind11;
using namespace py::literals;

void pyaf::wrapper::wrap_sequence(py::handle scope)
{
	auto sequence_class = py::class_<aff3ct::runtime::Sequence, aff3ct::tools::Interface_clone, aff3ct::tools::Interface_get_set_n_frames, aff3ct::tools::Interface_is_done>(scope, "_Sequence",py::dynamic_attr());

	sequence_class.def(py::init<aff3ct::runtime::Task &, aff3ct::runtime::Task &, const size_t, const bool, const std::vector<size_t> &>(), "first"_a, "last"_a, "n_threads"_a = 1, "thread_pinning"_a = false, "puids"_a = std::vector<size_t>(), py::return_value_policy::take_ownership);
	sequence_class.def(py::init<aff3ct::runtime::Task &, const size_t, const bool, const std::vector<size_t> &>(), "first"_a, "n_threads"_a = 1, "thread_pinning"_a = false, "puids"_a = std::vector<size_t>(), py::return_value_policy::take_ownership);
	sequence_class.def(py::init<const std::vector<aff3ct::runtime::Task *> &, const size_t, const bool, const std::vector<size_t> &, const bool>(), "firsts"_a, "n_threads"_a = 1, "thread_pinning"_a = false, "puids"_a = std::vector<size_t>(), "tasks_inplace"_a = true,py::return_value_policy::take_ownership);
	sequence_class.def(py::init<const std::vector<aff3ct::runtime::Task *> &, const std::vector<aff3ct::runtime::Task *> &, const std::vector<aff3ct::runtime::Task *> &, const size_t, const bool, const std::vector<size_t> &, const bool>(), "firsts"_a, "lasts"_a, "exclusions"_a, "n_threads"_a = 1, "thread_pinning"_a = false, "puids"_a = std::vector<size_t>(), "tasks_inplace"_a = true,py::return_value_policy::take_ownership);
	/*sequence_class.def(py::init<const std::vector<const aff3ct::runtime::Task *> &, const std::vector<const aff3ct::runtime::Task *> &, const std::vector<const aff3ct::runtime::Task *> &, const size_t, const bool, const std::vector<size_t> &>(), "firsts"_a, "lasts"_a, "exclusions"_a, "n_threads"_a = 1, "thread_pinning"_a = false, "puids"_a = std::vector<size_t>());
	sequence_class.def(py::init<const std::vector<aff3ct::runtime::Task *> &, const size_t, const bool, const std::vector<size_t> &, const bool>(), "firsts"_a, "n_threads"_a = 1, "thread_pinning"_a = false, "puids"_a = std::vector<size_t>(), "tasks_inplace"_a = true);
	sequence_class.def(py::init<const std::vector<aff3ct::runtime::Task *> &, const std::vector<aff3ct::runtime::Task *> &, const size_t, const bool, const std::vector<size_t> &, const bool>(), "firsts"_a, "lasts"_a, "n_threads"_a = 1, "thread_pinning"_a = false, "puids"_a = std::vector<size_t>(), "tasks_inplace"_a = true);
	sequence_class.def(py::init<const std::vector<aff3ct::runtime::Task *> &, const std::vector<aff3ct::runtime::Task *> &, const std::vector<aff3ct::runtime::Task *> &, const size_t, const bool, const std::vector<size_t> &, const bool>(), "firsts"_a, "lasts"_a, "exclusions"_a, "n_threads"_a = 1, "thread_pinning"_a = false, "puids"_a = std::vector<size_t>(), "tasks_inplace"_a = true);
	sequence_class.def(py::init<aff3ct::runtime::Task &, const size_t, const bool, const std::vector<size_t> &, const bool>(), "first"_a, "n_threads"_a = 1, "thread_pinning"_a = false, "puids"_a = std::vector<size_t>(), "tasks_inplace"_a = true);
	sequence_class.def(py::init<aff3ct::runtime::Task &, aff3ct::runtime::Task &, const size_t, const bool, const std::vector<size_t> &, const bool>(), "first"_a, "last"_a, "n_threads"_a = 1, "thread_pinning"_a = false, "puids"_a = std::vector<size_t>(), "tasks_inplace"_a = true);*/
	//sequence_class.def("exec", [](aff3ct::runtime::Sequence& self, std::function<bool(const std::vector<const int*>&)> stop_condition){self.exec(stop_condition);});
	sequence_class.def("exec", [](aff3ct::runtime::Sequence& self)
	{
		py::gil_scoped_release release{};
		self.exec();
	});

	sequence_class.def("exec_n_times", [](aff3ct::runtime::Sequence& self, size_t n_exec=1)
	{
		py::gil_scoped_release release{};
		std::atomic<size_t> counter(0);
		self.exec([&counter, n_exec]() { return ++counter >= n_exec; });
	});

	sequence_class.def("exec", [](aff3ct::runtime::Sequence& self, aff3ct::tools::Terminal_dump& terminal, std::ostream& stats_file)
	{
		py::gil_scoped_release release{};
		self.exec([&]() -> bool
		{
			py::gil_scoped_acquire gil;
			terminal.temp_report(stats_file);
			return false;
		});
	});

	sequence_class.def("exec_seq",  &aff3ct::runtime::Sequence::exec_seq,  "tid"_a = 0, "frame_id"_a = -1, py::call_guard<py::gil_scoped_release>());
	sequence_class.def("exec_step", &aff3ct::runtime::Sequence::exec_step, "tid"_a = 0, "frame_id"_a = -1, py::return_value_policy::reference, py::call_guard<py::gil_scoped_release>());

	sequence_class.def("export_dot", [](aff3ct::runtime::Sequence& self, const std::string& file_name){
		std::ofstream f(file_name);
		self.export_dot(f);
	});

	sequence_class.def("show_stats", [](aff3ct::runtime::Sequence& self, const bool ordered = false, const bool display_thr = true)
	{
		py::scoped_ostream_redirect stream(
			std::cout,                               // std::ostream&
			py::module_::import("sys").attr("stdout")// Python output
		);
		aff3ct::tools::Stats::show(self.get_modules_per_types(), ordered, display_thr);
	}, "ordered"_a=false, "display_thr"_a=true);

	sequence_class.def("get_modules_per_threads", &aff3ct::runtime::Sequence::get_modules_per_threads,                        py::return_value_policy::reference);
	sequence_class.def("get_modules_per_types",   &aff3ct::runtime::Sequence::get_modules_per_types,                          py::return_value_policy::reference);
	sequence_class.def("get_tasks_per_threads",   &aff3ct::runtime::Sequence::get_tasks_per_threads,                          py::return_value_policy::reference);
	sequence_class.def("get_tasks_per_types",     &aff3ct::runtime::Sequence::get_tasks_per_types,                            py::return_value_policy::reference);

	sequence_class.def_property_readonly("last_tasks",  &aff3ct::runtime::Sequence::get_lasts_tasks,  py::return_value_policy::reference);
	sequence_class.def_property_readonly("first_tasks", &aff3ct::runtime::Sequence::get_firsts_tasks, py::return_value_policy::reference);
	sequence_class.def_property("no_copy_mode",	&aff3ct::runtime::Sequence::is_no_copy_mode, &aff3ct::runtime::Sequence::set_no_copy_mode);
};

