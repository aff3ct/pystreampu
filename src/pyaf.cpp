#include "pyaf.hpp"

#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>

#include <aff3ct-core.hpp>

namespace py = pybind11;
using namespace aff3ct;
using namespace py::literals;

#define PYBIND11_DETAILED_ERROR_MESSAGES

PYBIND11_MODULE(_ext, m){
	setControlMode(rang::control::Force);
	m.def("enable_colors", [](){setControlMode(rang::control::Force);});
	m.def("disable_colors",[](){setControlMode(rang::control::Off);});

	 //Split in two following https:pybind11.readthedocs.io/en/stable/advanced/misc.html#avoiding-c-types-in-docstrings
	 //for enhancing python doc

	// Interfaces
	py::module_ submod_itf   = m.def_submodule("interfaces"); // TODO : put in a separate file
	pyaf::wrapper::wrap_interface_clone           (submod_itf);
	pyaf::wrapper::wrap_interface_is_done         (submod_itf);
	pyaf::wrapper::wrap_interface_reset           (submod_itf);
	pyaf::wrapper::wrap_interface_get_set_n_frames(submod_itf);
	pyaf::wrapper::wrap_interface_set_seed        (submod_itf);
	pyaf::wrapper::wrap_interface_waiting         (submod_itf);

	// Wrap of runtime namespace
	py::module_ m_core = m.def_submodule("core"); // TODO rename runtime
	pyaf::wrapper::wrap_socket(m_core);
	pyaf::wrapper::wrap_task(m_core);

	auto wrap_module(std::unique_ptr<pyaf::wrapper::Wrapper_py>(new pyaf::wrapper::Wrapper_Module(m_core))); // TODO Update to the new way
	wrap_module->definitions();

	// Wrap of tools namespace
	// dtypes (class for handling types in the python package)
	pyaf::wrapper::wrap_dtypes(m);

	pyaf::wrapper::wrap_fmtflags(m);

	// Rang
	py::module_ m_rang = m.def_submodule("rang");
	pyaf::wrapper::wrap_rang_flags(m_rang);


	// Exceptions
	py::module_ submod_exc   = m.def_submodule("exceptions");
	pyaf::wrapper::wrap_exceptions(submod_exc);

	py::module_ submod_rep   = m.def_submodule("reporter");
	pyaf::wrapper::wrap_reporter(submod_rep);

	py::module_ submod_ter   = m.def_submodule("terminal");
	pyaf::wrapper::wrap_terminal(submod_ter);

	// Help
	// TODO : put in a separate file
	m.def("help", [](const aff3ct::module::Module  & module, const bool & verbose){py::print(aff3ct::tools::get_help(module, verbose).c_str());}, "module"_a, "verbose"_a=false);
	m.def("help", [](const aff3ct::runtime::Task   &   task, const bool & verbose){py::print(aff3ct::tools::get_help(task,   verbose).c_str());}, "task"_a,   "verbose"_a=false);
	m.def("help", [](const aff3ct::runtime::Socket & socket, const bool & verbose){py::print(aff3ct::tools::get_help(socket, verbose).c_str());}, "socket"_a, "verbose"_a=false);

	// Wrap of module namespace
	pyaf::wrapper::wrap_range    (m); // TODO : change python submodule
	pyaf::wrapper::wrap_slicer   (m); // TODO : change python submodule
	pyaf::wrapper::wrap_stateless(m); // TODO : change python submodule

	py::module_ submod_arr = m.def_submodule("arr");
	pyaf::wrapper::wrap_array(submod_arr);

	py::module_ submod_bop = m.def_submodule("bop");
	pyaf::wrapper::wrap_binaryop(submod_bop);

	py::module_ submod_inc = m.def_submodule("inc");
	pyaf::wrapper::wrap_incrementer(submod_inc);

	py::module_ submod_ini = m.def_submodule("ini");
	pyaf::wrapper::wrap_initializer(submod_ini);

	py::module_ submod_ite = m.def_submodule("ite");
	pyaf::wrapper::wrap_iterator(submod_ite);

	py::module_ submod_dly = m.def_submodule("dly");
	pyaf::wrapper::wrap_delayer(submod_dly);

	py::module_ submod_fin = m.def_submodule("fin");
	pyaf::wrapper::wrap_finalizer(submod_fin);

	py::module_ submod_prb = m.def_submodule("prb");
	pyaf::wrapper::wrap_probe(submod_prb);

	py::module_ submod_red = m.def_submodule("red");
	pyaf::wrapper::wrap_reducer(submod_red);

	py::module_ submod_src = m.def_submodule("src");
	pyaf::wrapper::wrap_source             (submod_src); // TODO : put in a separate file
	pyaf::wrapper::wrap_source_random      (submod_src); // TODO : put in a separate file
	pyaf::wrapper::wrap_source_user        (submod_src); // TODO : put in a separate file
	pyaf::wrapper::wrap_source_user_binary (submod_src); // TODO : put in a separate file

	py::module_ submod_swi = m.def_submodule("swi");
	pyaf::wrapper::wrap_switcher(submod_swi);

	py::module_ submod_sse = m.def_submodule("sse");
	pyaf::wrapper::wrap_subsequence(submod_sse);

	py::module_ submod_uop = m.def_submodule("uop");
	pyaf::wrapper::wrap_unaryop(submod_uop);

	pyaf::wrapper::wrap_sequence(m_core);

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

}

