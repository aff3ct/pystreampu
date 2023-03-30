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
PYBIND11_MODULE(builtins, m){
	// Split in two following https://pybind11.readthedocs.io/en/stable/advanced/misc.html#avoiding-c-types-in-docstrings
	// for enhancing python doc
	//setControlMode(rang::control::Off);
	m.attr("__name__") = "pyaf.builtins";

	m.doc() =
R"pbdoc(
        Python bindings for AFF3CT library.

        .. autosummary::
           :toctree:
           :template: custom-module-template.rst

		   help
           tools
)pbdoc";

	pyaf::wrapper::wrap_dtypes(m);

	py::module_ submod_tools = m.def_submodule("tools");
	py::module_ submod_itf   = m.def_submodule("interfaces");
	pyaf::wrapper::wrap_interface_clone           (submod_itf);
	pyaf::wrapper::wrap_interface_is_done         (submod_itf);
	pyaf::wrapper::wrap_interface_reset           (submod_itf);
	pyaf::wrapper::wrap_interface_get_set_n_frames(submod_itf);

	py::module_ m_core = m.def_submodule("core");
	std::string doc_m_core =
R"pbdoc(
        Bindings for AFF3CT-CORE.

        .. autosummary::
           :toctree:
           :template: custom-module-template.rst
)pbdoc";
	m_core.doc() = doc_m_core.c_str();

	std::vector<std::unique_ptr<pyaf::wrapper::Wrapper_py>> wrappers;


	wrappers.push_back(std::unique_ptr<pyaf::wrapper::Wrapper_py>(new pyaf::wrapper::Wrapper_Socket(m_core)));
	wrappers.push_back(std::unique_ptr<pyaf::wrapper::Wrapper_py>(new pyaf::wrapper::Wrapper_Task  (m_core)));
	wrappers.push_back(std::unique_ptr<pyaf::wrapper::Wrapper_py>(new pyaf::wrapper::Wrapper_Module(m_core)));

	for (size_t i = 0; i < wrappers.size(); i++)
		wrappers[i]->definitions();


	pyaf::wrapper::wrap_sequence(m_core);

	m.def("help", [](const aff3ct::module::Module  & module, const bool & verbose){py::print(aff3ct::tools::get_help(module, verbose).c_str());}, "module"_a, "verbose"_a=false);
	m.def("help", [](const aff3ct::runtime::Task   &   task, const bool & verbose){py::print(aff3ct::tools::get_help(task,   verbose).c_str());}, "module"_a, "verbose"_a=false);
	m.def("help", [](const aff3ct::runtime::Socket & socket, const bool & verbose){py::print(aff3ct::tools::get_help(socket, verbose).c_str());}, "module"_a, "verbose"_a=false);

	py::module_ submod_arr = m.def_submodule("arr");
	pyaf::wrapper::wrap_array(submod_arr);

	pyaf::wrapper::wrap_range(m);

	py::module_ submod_bop = m.def_submodule("bop");
	pyaf::wrapper::wrap_binaryop(submod_bop);

	py::module_ submod_red = m.def_submodule("red");
	pyaf::wrapper::wrap_reducer(submod_red);

	py::module_ submod_swi = m.def_submodule("swi");
	pyaf::wrapper::wrap_switcher(submod_swi);

	py::module_ submod_sse = m.def_submodule("sse");
	pyaf::wrapper::wrap_subsequence(submod_sse);

	py::module_ submod_uop = m.def_submodule("uop");
	pyaf::wrapper::wrap_unaryop(submod_uop);

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

}

