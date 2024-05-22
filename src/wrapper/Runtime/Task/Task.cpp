#include <pybind11/stl.h>
#include "wrapper/Runtime/Task/Task.hpp"
#include "wrapper/Runtime/Socket/Socket.hpp"
#include "wrapper/Module/Array/Array.hpp"

#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/chrono.h>
#include <rang.hpp>
#include <chrono>
namespace py = pybind11;
using namespace py::literals;
using namespace spu::module;
using namespace pyaf::wrapper;
using namespace spu::runtime;

void pyaf::wrapper::wrap_task(py::handle scope)
{
	py::class_ <spu::runtime::Task> py_task(scope, "Task");

	py::enum_<status_t>(py_task, "Status", "Enumeration of tasks return code.")
      .value("SUCCESS",      status_t::SUCCESS,      "Success code"     )
	  .value("FAILURE",      status_t::FAILURE,      "Failure code"     )
	  .value("FAILURE_STOP", status_t::FAILURE_STOP, "Failure stop code")
	  .value("UNKNOWN",      status_t::UNKNOWN,      "Unknown code"     );

	py_task.def_property_readonly("name",    &spu::runtime::Task::get_name);
	py_task.def_property_readonly("sockets", [](spu::runtime::Task& t)
	{
		std::vector<spu::runtime::Socket*> sckts;

		for(auto s:t.sockets)
			sckts.push_back(s.get());
		return sckts;
	});

	py_task.def("can_exec", &spu::runtime::Task::can_exec);

	py_task.def("interrupt_processing", [](spu::runtime::Task& t){
		throw spu::tools::processing_aborted();
	});

	py_task.def_property_readonly("inputs", [](spu::runtime::Task& t)
	{
		std::vector<spu::runtime::Socket*> in;

		for(auto s:t.sockets)
			if (s->get_type() == spu::runtime::socket_t::SIN)
				in.push_back(s.get());

		return in;
	});

	py_task.def_property_readonly("forwards", [](spu::runtime::Task& t)
	{
		std::vector<spu::runtime::Socket*> fwd;

		for(auto s:t.sockets)
			if (s->get_type() == spu::runtime::socket_t::SFWD)
				fwd.push_back(s.get());

		return fwd;
	});

	py_task.def_property_readonly("outputs", [](spu::runtime::Task& t)
	{
		std::vector<spu::runtime::Socket*> out;
		auto sockets = t.sockets;
		for(auto s:t.sockets)
			if (s->get_type() == spu::runtime::socket_t::SOUT)
				out.push_back(s.get());
		return out;
	});

	py_task.def("exec",
		[](spu::runtime::Task &self, const int frame_id, const bool managed_memory)
		{
			py::scoped_ostream_redirect stream(
			std::cout,                                // std::ostream&
			py::module_::import("sys").attr("stdout") // Python output
			);
			//setControlMode(rang::control::Force);
			self.exec(frame_id, managed_memory);
		},
		"frame_id"_a = -1, "managed_memory"_a = true);
	py_task.def("__getitem__",  [](spu::runtime::Task& t, const std::string& s)
	{
		auto& m = t.get_module();
		return py::cast(&m[t.get_name() + "::" + s]);
	});
	py_task.def_property_readonly("module", &spu::runtime::Task::get_module);
	py_task.def_property("debug", &spu::runtime::Task::is_debug, &spu::runtime::Task::set_debug);
	py_task.def_property("stats", &spu::runtime::Task::is_stats, &spu::runtime::Task::set_stats);
	py_task.def_property("fast" , &spu::runtime::Task::is_fast,  &spu::runtime::Task::set_fast );
	py_task.def_property_readonly("n_calls",         &spu::runtime::Task::get_n_calls       );
	py_task.def_property_readonly("total_duration", [](const spu::runtime::Task& self)
	{
		if(self.is_stats())
			return std::chrono::duration<double>(self.get_duration_total()).count();
		else
			return double(0.0f);
	});
	py_task.def_property_readonly("avg_duration", [](const spu::runtime::Task& self)
	{
		if(self.is_stats())
			return std::chrono::duration<double>(self.get_duration_avg()).count();
		else
			return double(0.0f);
	});
	py_task.def_property_readonly("min_duration", [](const spu::runtime::Task& self)
	{
		if(self.is_stats())
			return std::chrono::duration<double>(self.get_duration_min()).count();
		else
			return double(0.0f);
	});
	py_task.def_property_readonly("max_duration", [](const spu::runtime::Task& self)
	{
		if(self.is_stats())
			return std::chrono::duration<double>(self.get_duration_max()).count();
		else
			return double(0.0f);
	});
	py_task.def("reset", &spu::runtime::Task::reset);
	py_task.def("bind", [](spu::runtime::Task& self, spu::runtime::Socket& s_out, const int priority)
	{
		self.bind(s_out, priority);
	}, "Binds the Task to socket 's_out' with priority 'priority'.", "s_out"_a, "priority"_a=-1);
	py_task.def("bind", [](spu::runtime::Task& self, spu::runtime::Task& t_out, const int priority)
	{
		self.bind(t_out, priority);
	}, "Binds the Task to task 't_out' with priority 'priority'.", "t_out"_a, "priority"_a=-1);

	// py_task.def("is_bound"           , &spu::runtime::Task::is_bound                          );
	py_task.def("set_debug_hex"      , &spu::runtime::Task::set_debug_hex      , "debug_hex"_a);
	py_task.def("set_debug_limit"    , &spu::runtime::Task::set_debug_limit    , "limit"_a    );
	py_task.def("set_debug_precision", &spu::runtime::Task::set_debug_precision, "prec"_a     );
	py_task.def("set_debug_frame_max", &spu::runtime::Task::set_debug_frame_max, "limit"_a    );

};
