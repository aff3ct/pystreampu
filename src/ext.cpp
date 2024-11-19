#include "ext.hpp"

#include <string>
#include <thread>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>

#include <streampu.hpp>

namespace py = pybind11;
using namespace spu;
using namespace py::literals;

#define PYBIND11_DETAILED_ERROR_MESSAGES

PYBIND11_MODULE(_ext, m)
{
    m.def("get_hardware_concurrency", &std::thread::hardware_concurrency);
    // Split in two following
    // https:pybind11.readthedocs.io/en/stable/advanced/misc.html#avoiding-c-types-in-docstrings
    // for enhancing python doc

    // Interfaces
    py::module_ submod_itf = m.def_submodule("interfaces"); // TODO : put in a separate file
    pyspu::wrapper::wrap_interface_clone(submod_itf);
    pyspu::wrapper::wrap_interface_is_done(submod_itf);
    pyspu::wrapper::wrap_interface_reset(submod_itf);
    pyspu::wrapper::wrap_interface_get_set_n_frames(submod_itf);
    pyspu::wrapper::wrap_interface_set_seed(submod_itf);
    pyspu::wrapper::wrap_interface_waiting(submod_itf);

    // Wrap of runtime namespace
    py::module_ m_core = m.def_submodule("core"); // TODO rename runtime
    pyspu::wrapper::wrap_socket(m_core);
    pyspu::wrapper::wrap_task(m_core);

    auto wrap_module(std::unique_ptr<pyspu::wrapper::Wrapper_py>(
      new pyspu::wrapper::Wrapper_Module(m_core))); // TODO Update to the new way
    wrap_module->definitions();

    // Wrap of tools namespace
    // dtypes (class for handling types in the python package)
    pyspu::wrapper::wrap_dtypes(m);

    pyspu::wrapper::wrap_fmtflags(m);

    pyspu::wrapper::wrap_signal_handler(m);

    // Rang
    py::module_ m_rang = m.def_submodule("rang");
    pyspu::wrapper::wrap_rang_flags(m_rang);

    // Exceptions
    py::module_ submod_exc = m.def_submodule("exceptions");
    pyspu::wrapper::wrap_exceptions(submod_exc);

    py::module_ submod_rep = m.def_submodule("reporter");
    pyspu::wrapper::wrap_reporter(submod_rep);

    py::module_ submod_ter = m.def_submodule("terminal");
    pyspu::wrapper::wrap_terminal(submod_ter);

    // Help
    // TODO : put in a separate file
    m.def(
      "help",
      [](const spu::module::Module& module, const bool& verbose)
      { py::print(spu::tools::get_help(module, verbose).c_str()); },
      "module"_a,
      "verbose"_a = false);
    m.def(
      "help",
      [](const spu::runtime::Task& task, const bool& verbose)
      { py::print(spu::tools::get_help(task, verbose).c_str()); },
      "task"_a,
      "verbose"_a = false);
    m.def(
      "help",
      [](const spu::runtime::Socket& socket, const bool& verbose)
      { py::print(spu::tools::get_help(socket, verbose).c_str()); },
      "socket"_a,
      "verbose"_a = false);

    // Wrap of module namespace
    py::module_ submod_ada = m.def_submodule("ada");
    pyspu::wrapper::wrap_adaptors(submod_ada);

    py::module_ submod_ctl = m.def_submodule("ctl");
    pyspu::wrapper::wrap_controllers(submod_ctl);

    py::module_ submod_ran = m.def_submodule("ran");
    pyspu::wrapper::wrap_range(submod_ran);

    py::module_ submod_sli = m.def_submodule("sli");
    pyspu::wrapper::wrap_slicer(submod_sli);

    py::module_ submod_sts = m.def_submodule("sts");
    pyspu::wrapper::wrap_stateless(submod_sts); // TODO : change python submodule

    py::module_ submod_arr = m.def_submodule("arr");
    pyspu::wrapper::wrap_array(submod_arr);

    py::module_ submod_bop = m.def_submodule("bop");
    pyspu::wrapper::wrap_binaryop(submod_bop);

    py::module_ submod_inc = m.def_submodule("inc");
    pyspu::wrapper::wrap_incrementer(submod_inc);

    py::module_ submod_ini = m.def_submodule("ini");
    pyspu::wrapper::wrap_initializer(submod_ini);

    py::module_ submod_ite = m.def_submodule("ite");
    pyspu::wrapper::wrap_iterator(submod_ite);

    py::module_ submod_dly = m.def_submodule("dly");
    pyspu::wrapper::wrap_delayer(submod_dly);

    py::module_ submod_fin = m.def_submodule("fin");
    pyspu::wrapper::wrap_finalizer(submod_fin);

    py::module_ submod_prb = m.def_submodule("prb");
    pyspu::wrapper::wrap_probe(submod_prb);

    py::module_ submod_red = m.def_submodule("red");
    pyspu::wrapper::wrap_reducer(submod_red);

    py::module_ submod_rel = m.def_submodule("rel");
    pyspu::wrapper::wrap_relayer(submod_rel);

    py::module_ submod_src = m.def_submodule("src");
    pyspu::wrapper::wrap_source(submod_src);             // TODO : put in a separate file
    pyspu::wrapper::wrap_source_random(submod_src);      // TODO : put in a separate file
    pyspu::wrapper::wrap_source_user(submod_src);        // TODO : put in a separate file
    pyspu::wrapper::wrap_source_user_binary(submod_src); // TODO : put in a separate file

    py::module_ submod_snk = m.def_submodule("snk");
    pyspu::wrapper::wrap_sinks(submod_snk);

    py::module_ submod_swi = m.def_submodule("swi");
    pyspu::wrapper::wrap_switcher(submod_swi);

    py::module_ submod_slp = m.def_submodule("slp");
    pyspu::wrapper::wrap_sleeper(submod_slp);

    py::module_ submod_set = m.def_submodule("set");
    pyspu::wrapper::wrap_set(submod_set);

    py::module_ submod_uop = m.def_submodule("uop");
    pyspu::wrapper::wrap_unaryop(submod_uop);

    pyspu::wrapper::wrap_sequence(m_core);
    pyspu::wrapper::wrap_pipeline(m_core);
}
