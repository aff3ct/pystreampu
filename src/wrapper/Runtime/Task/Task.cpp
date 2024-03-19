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
using namespace aff3ct::module;
using namespace pyaf::wrapper;
using namespace aff3ct::runtime;

void pyaf::wrapper::wrap_task(py::handle scope)
{
	py::class_ <aff3ct::runtime::Task, aff3ct::runtime::Task_Publicist> py_task(scope, "Task");

	py::enum_<status_t>(py_task, "Status", "Enumeration of tasks return code.")
      .value("SUCCESS",      status_t::SUCCESS,      "Success code"     )
	  .value("FAILURE",      status_t::FAILURE,      "Failure code"     )
	  .value("FAILURE_STOP", status_t::FAILURE_STOP, "Failure stop code")
	  .value("UNKNOWN",      status_t::UNKNOWN,      "Unknown code"     );

	py_task.def_property_readonly("name",    &aff3ct::runtime::Task::get_name);
	py_task.def_property_readonly("sockets", [](aff3ct::runtime::Task& t)
	{
		std::vector<aff3ct::runtime::Socket*> sckts;

		for(auto s:t.sockets)
			sckts.push_back(s.get());
		return sckts;
	});

	py_task.def("can_exec", &aff3ct::runtime::Task::can_exec);

	py_task.def("interrupt_processing", [](aff3ct::runtime::Task& t){
		throw aff3ct::tools::processing_aborted();
	});

	py_task.def_property_readonly("inputs", [](aff3ct::runtime::Task& t)
	{
		std::vector<aff3ct::runtime::Socket*> in;

		for(auto s:t.sockets)
			if (s->get_type() == aff3ct::runtime::socket_t::SIN)
				in.push_back(s.get());

		return in;
	});

	py_task.def_property_readonly("forwards", [](aff3ct::runtime::Task& t)
	{
		std::vector<aff3ct::runtime::Socket*> fwd;

		for(auto s:t.sockets)
			if (s->get_type() == aff3ct::runtime::socket_t::SFWD)
				fwd.push_back(s.get());

		return fwd;
	});

	py_task.def_property_readonly("outputs", [](aff3ct::runtime::Task& t)
	{
		std::vector<aff3ct::runtime::Socket*> out;
		auto sockets = t.sockets;
		for(auto s:t.sockets)
			if (s->get_type() == aff3ct::runtime::socket_t::SOUT)
				out.push_back(s.get());
		return out;
	});

	py_task.def("exec",
		[](aff3ct::runtime::Task &self, const int frame_id, const bool managed_memory)
		{
			py::scoped_ostream_redirect stream(
			std::cout,                                // std::ostream&
			py::module_::import("sys").attr("stdout") // Python output
			);
			//setControlMode(rang::control::Force);
			self.exec(frame_id, managed_memory);
		},
		"frame_id"_a = -1, "managed_memory"_a = true);
	py_task.def("__getitem__",  [](aff3ct::runtime::Task& t, const std::string& s)
	{
		auto& m = t.get_module();
		return py::cast(&m[t.get_name() + "::" + s]);
	});
	py_task.def_property_readonly("module", &aff3ct::runtime::Task::get_module);
	py_task.def_property("debug", &aff3ct::runtime::Task::is_debug, &aff3ct::runtime::Task::set_debug);
	py_task.def_property("stats", &aff3ct::runtime::Task::is_stats, &aff3ct::runtime::Task::set_stats);
	py_task.def_property("fast" , &aff3ct::runtime::Task::is_fast,  &aff3ct::runtime::Task::set_fast );
	py_task.def_property_readonly("n_calls",         &aff3ct::runtime::Task::get_n_calls       );
	py_task.def_property_readonly("total_duration", [](const aff3ct::runtime::Task& self)
	{
		if(self.is_stats())
			return std::chrono::duration<double>(self.get_duration_total()).count();
		else
			return double(0.0f);
	});
	py_task.def_property_readonly("avg_duration", [](const aff3ct::runtime::Task& self)
	{
		if(self.is_stats())
			return std::chrono::duration<double>(self.get_duration_avg()).count();
		else
			return double(0.0f);
	});
	py_task.def_property_readonly("min_duration", [](const aff3ct::runtime::Task& self)
	{
		if(self.is_stats())
			return std::chrono::duration<double>(self.get_duration_min()).count();
		else
			return double(0.0f);
	});
	py_task.def_property_readonly("max_duration", [](const aff3ct::runtime::Task& self)
	{
		if(self.is_stats())
			return std::chrono::duration<double>(self.get_duration_max()).count();
		else
			return double(0.0f);
	});
	py_task.def("reset", &aff3ct::runtime::Task::reset);
	py_task.def("bind", [](aff3ct::runtime::Task& self, aff3ct::runtime::Socket& s_out, const int priority)
	{
		self.bind(s_out, priority);
	}, "Binds the Task to socket 's_out' with priority 'priority'.", "s_out"_a, "priority"_a=1);

	// py_task.def("is_bound"           , &aff3ct::runtime::Task::is_bound                          );
	py_task.def("set_debug_hex"      , &aff3ct::runtime::Task::set_debug_hex      , "debug_hex"_a);
	py_task.def("set_debug_limit"    , &aff3ct::runtime::Task::set_debug_limit    , "limit"_a    );
	py_task.def("set_debug_precision", &aff3ct::runtime::Task::set_debug_precision, "prec"_a     );
	py_task.def("set_debug_frame_max", &aff3ct::runtime::Task::set_debug_frame_max, "limit"_a    );

};
