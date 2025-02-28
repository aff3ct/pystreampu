#include "wrapper/Module/Stateful/Stateful/Stateful.hpp"
#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_functions.h"

namespace py = pybind11;
using namespace py::literals;
using namespace spu::module;

void
pyspu::wrapper::wrap_stateful(py::handle scope)
{
    auto stateful_class = py::class_<spu::module::Stateful, spu::module::Module, spu::module::Stateful_Publicist>(scope,"Stateful",
                                                                                        R"pbdoc(
        Stateful modules are modules that cannot be cloned due to internal state
        )pbdoc");
    stateful_class.def(py::init<>());
    stateful_class.def(py::init<const Stateful&>());


    stateful_class.def_property("n_frames_per_wave", &Stateful::get_n_frames_per_wave, &Stateful_Publicist::set_n_frames_per_wave);

    stateful_class.def(
      "create_socket_in",
      [](Stateful_Publicist& mdl,
         spu::runtime::Task& task,
         const std::string& name,
         const size_t n_elmts,
         const pyspu::dtype dtype)
      { return mdl.create_socket_in(task, name, n_elmts, pyspu::utils::str2typeid(dtype.get_name())); },
      "task"_a,
      "name"_a,
      "n_elmts"_a,
      "dtype"_a,
      R"pbdoc(
        Create a new input socket to a task.
    )pbdoc");

    stateful_class.def(
      "create_socket_out",
      [](Stateful_Publicist& mdl,
         spu::runtime::Task& task,
         const std::string& name,
         const size_t n_elmts,
         const pyspu::dtype dtype)
      { return mdl.create_socket_out(task, name, n_elmts, pyspu::utils::str2typeid(dtype.get_name())); },
      "task"_a,
      "name"_a,
      "n_elmts"_a,
      "dtype"_a,
      R"pbdoc(
        Create a new output socket to a task.
    )pbdoc");

    stateful_class.def(
      "create_socket_fwd",
      [](Stateful_Publicist& mdl,
         spu::runtime::Task& task,
         const std::string& name,
         const size_t n_elmts,
         const pyspu::dtype dtype)
      { return mdl.create_socket_fwd(task, name, n_elmts, pyspu::utils::str2typeid(dtype.get_name())); },
      "task"_a,
      "name"_a,
      "n_elmts"_a,
      "dtype"_a,
      R"pbdoc(
        Create a new forward socket to a task.
    )pbdoc");

    stateful_class.def(
      "create_task",
      [](Stateful_Publicist& mdl, const std::string& name) { return &mdl.create_task(name); },
      "name"_a,
      R"pbdoc(
        Create a new task.

        Args:
            name (str): name of the task

        Returns:
            Task: newly created task.

    )pbdoc",
      py::return_value_policy::reference);

    stateful_class.def("create_codelet", &Stateful_Publicist::create_codelet);

    stateful_class.def("deep_copy", &Stateful_Publicist::deep_copy);

}
