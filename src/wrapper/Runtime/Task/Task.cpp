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
	py::class_ <aff3ct::runtime::Task, std::shared_ptr<aff3ct::runtime::Task>, aff3ct::runtime::Task_Publicist> py_task(scope, "Task");

	py_task.def_property_readonly("name",    &aff3ct::runtime::Task::get_name);
	py_task.def_property_readonly("doc", &aff3ct::runtime::Task::get_doc);
	py_task.def_property_readonly("sockets", [](aff3ct::runtime::Task& t) -> std::vector<std::shared_ptr<aff3ct::runtime::Socket>>
	{
		return t.sockets;
	});

	py_task.def("can_exec",&aff3ct::runtime::Task::can_exec);

	py_task.def_property_readonly("inputs", [](aff3ct::runtime::Task& t)
	{
		std::vector<aff3ct::runtime::Socket*> in;

		for(auto s:t.sockets)
			if (t.get_socket_type(*s) == aff3ct::runtime::socket_t::SIN)
				in.push_back(s.get());

		return in;
	});

	py_task.def_property_readonly("forwards", [](aff3ct::runtime::Task& t)
	{
		std::vector<aff3ct::runtime::Socket*> fwd;

		for(auto s:t.sockets)
			if (t.get_socket_type(*s) == aff3ct::runtime::socket_t::SFWD)
				fwd.push_back(s.get());

		return fwd;
	});

	py_task.def_property_readonly("outputs", [](aff3ct::runtime::Task& t)
	{
		std::vector<aff3ct::runtime::Socket*> out;
		auto sockets = t.sockets;
		for(auto s:t.sockets)
			if (t.get_socket_type(*s) == aff3ct::runtime::socket_t::SOUT)
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
	}, py::return_value_policy::reference);
	py_task.def_property_readonly("module", &aff3ct::runtime::Task::get_module, py::return_value_policy::reference);
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

	py_task.def("is_bound"           , &aff3ct::runtime::Task::is_bound                          );
	py_task.def("set_debug_hex"      , &aff3ct::runtime::Task::set_debug_hex      , "debug_hex"_a);
	py_task.def("set_debug_limit"    , &aff3ct::runtime::Task::set_debug_limit    , "limit"_a    );
	py_task.def("set_debug_precision", &aff3ct::runtime::Task::set_debug_precision, "prec"_a     );
	py_task.def("set_debug_frame_max", &aff3ct::runtime::Task::set_debug_frame_max, "limit"_a    );

	/*py_task.def("__call__", [](aff3ct::runtime::Task& self, py::args args, const py::kwargs& kwargs)
	{
		py::list outputs;
		std::vector<std::shared_ptr<aff3ct::runtime::Socket>> inputs;
		py::dict input_dict;
		for (auto & s : self.sockets)
			if(self.get_socket_type(*s.get()) == aff3ct::runtime::socket_t::SOUT)
			{
				if(s->get_name() != "status")
					outputs.append(py::cast(s.get()));
			}
			else
			{
				inputs.push_back(s);
				input_dict[py::cast(s->get_name())] = py::none();
			}

		aff3ct::runtime::Task * previous_tsk = nullptr;
		if (args)
		{
			for (auto i = 0; i < args.size(); i++)
			{
				try
				{
					aff3ct::runtime::Socket* in = args[i].cast<aff3ct::runtime::Socket*>();
					previous_tsk = &in->get_task();
				}
				catch(const std::exception & e){}
			}
		}
		if (kwargs)
		{
			if (kwargs.size()>0)
			{
			    for (auto item : kwargs)
				{
					std::string name = item.first.cast<std::string>();
					try
					{
						aff3ct::runtime::Socket* in = item.second.cast<aff3ct::runtime::Socket*>();
						previous_tsk = &in->get_task();
					}
					catch(const std::exception & e){}
				}
			}
		}
		py::object py_mod = py::cast(self.get_module());
		py_mod.attr("__data__") = py::dict();

		if (args)
		{
			for (auto i = 0; i < args.size(); i++)
			{
				inputs[i]->reset();
				try
				{
					aff3ct::runtime::Socket* in = args[i].cast<aff3ct::runtime::Socket*>();
					previous_tsk = &in->get_task();
					inputs[i]->bind(*in);
				}
				catch(const std::exception & e)
				{
					py::object in = py::array(args[i]);
					if (previous_tsk != nullptr)
					{
						auto in_array = new aff3ct::module::Array(in);
						inputs[i]->bind((*in_array)["get::X"]);
						(*in_array)("get").exec();
						(*in_array)("get").bind((previous_tsk->get_module())[previous_tsk->get_name() + "::status"]);
						input_dict[py::cast(inputs[i]->get_name())] = py::cast(std::unique_ptr<aff3ct::module::Array>(std::move(in_array)));
					}
					else
					{
						auto py_sckt = py::cast(inputs[i].get());
						py_sckt.attr("bind")(in);
						input_dict[py::cast(inputs[i]->get_name())] = in;
					}
				}
			}
		}
		if (kwargs)
		{
			if (kwargs.size()>0)
			{
				//std::map<std::string, aff3ct::runtime::Socket*> cppmap;
				//cppmap = kwargs.cast<std::map<std::string, aff3ct::runtime::Socket*>>();

			    for (auto item : kwargs)
				{
					std::string name = item.first.cast<std::string>();
					try
					{
						aff3ct::runtime::Socket* in = item.second.cast<aff3ct::runtime::Socket*>();
						previous_tsk = &in->get_task();
						aff3ct::runtime::Socket& s  = self.get_module()[self.get_name() + "::" + name];
						s.reset();
						s.bind(*in);
					}
					catch(const std::exception & e)
					{
						py::object in = item.second.cast<py::array>();
						aff3ct::runtime::Socket& s  = self.get_module()[self.get_name() + "::" + name];
						s.reset();
						if (previous_tsk != nullptr)
						{
							auto in_array = new aff3ct::module::Array(in);
							s.bind((*in_array)["get::X"]);
							(*in_array)("get").exec();
							(*in_array)("get").bind((previous_tsk->get_module())[previous_tsk->get_name() + "::status"]);
							input_dict[py::cast(s.get_name())] = py::cast(std::unique_ptr<aff3ct::module::Array>(std::move(in_array)));
						}
						else
						{
							auto py_sckt = py::cast(&s);
							py_sckt.attr("bind")(in);
							input_dict[py::cast(s.get_name())] = in;
						}
					}
				}
				//for (auto & s : inputs)
				//{
				//	s->reset();
				//	s->bind(*cppmap[s->get_name()]);
				//}
			}
		}

		self.exec();

		py_mod.attr("__data__")[py::cast(self.get_name())] = input_dict;

		py::object returned_outputs;
		if(outputs.size() > 1)
			returned_outputs = py::tuple(outputs);
		else if (outputs.size() == 1)
			returned_outputs = outputs[0];
		else
			returned_outputs = py::none();
		return returned_outputs;
	}, py::return_value_policy::reference);*/


	/*py_task.def("__getattr__", [](aff3ct::runtime::Task& t, const std::string& attr){
		try
		{
			auto& m = t.get_module();
			return py::cast(&m[t.get_name() + "::" + attr]);
		}
		catch(const aff3ct::tools::invalid_argument& e)
		{
			throw py::attribute_error();
		}

	},"If 'attr' is a socket name, task.attr returns the corresponding socket.", "attr"_a, py::keep_alive<0,1>());
	py_task.def("__dir__", [](const aff3ct::runtime::Task& t){

		py::list ret = py::module::import("builtins").attr("object").attr("__dir__")(py::cast(t));
		for (auto & s : t.sockets)
			ret.append(py::cast(s->get_name()));
		return ret;
	});*/
};
