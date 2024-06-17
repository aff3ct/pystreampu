#include "wrapper/Runtime/Sequence/Sequence.hpp"

#include "wrapper/Common/pystreambuf.h"

#include <pybind11/functional.h>
#include <pybind11/iostream.h>
#include <pybind11/stl.h>

#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>

#include <streampu.hpp>

namespace py = pybind11;
using namespace py::literals;

void
pyaf::wrapper::wrap_sequence(py::handle scope)
{
    auto sequence_class = py::class_<spu::runtime::Sequence,
                                     spu::tools::Interface_clone,
                                     spu::tools::Interface_get_set_n_frames,
                                     spu::tools::Interface_is_done>(scope, "_Sequence", py::dynamic_attr());

    sequence_class.def(py::init<spu::runtime::Task&, const size_t, const bool, const std::vector<size_t>&>(),
                       "first"_a,
                       "n_threads"_a = 1,
                       "thread_pinning"_a = false,
                       "puids"_a = std::vector<size_t>(),
                       py::return_value_policy::take_ownership);
    sequence_class.def(
      py::init<spu::runtime::Task&, spu::runtime::Task&, const size_t, const bool, const std::vector<size_t>&>(),
      "first"_a,
      "last"_a,
      "n_threads"_a = 1,
      "thread_pinning"_a = false,
      "puids"_a = std::vector<size_t>(),
      py::return_value_policy::take_ownership);
    sequence_class.def(py::init<const std::vector<spu::runtime::Task*>&,
                                const size_t,
                                const bool,
                                const std::vector<size_t>&,
                                const bool>(),
                       "firsts"_a,
                       "n_threads"_a = 1,
                       "thread_pinning"_a = false,
                       "puids"_a = std::vector<size_t>(),
                       "tasks_inplace"_a = true,
                       py::return_value_policy::take_ownership);
    sequence_class.def(py::init<const std::vector<spu::runtime::Task*>&,
                                const std::vector<spu::runtime::Task*>&,
                                const std::vector<spu::runtime::Task*>&,
                                const size_t,
                                const bool,
                                const std::vector<size_t>&,
                                const bool>(),
                       "firsts"_a,
                       "lasts"_a,
                       "exclusions"_a,
                       "n_threads"_a = 1,
                       "thread_pinning"_a = false,
                       "puids"_a = std::vector<size_t>(),
                       "tasks_inplace"_a = true,
                       py::return_value_policy::take_ownership);
    /*sequence_class.def(py::init<const std::vector<const spu::runtime::Task *> &,
    const std::vector<const spu::runtime::Task *> &, const std::vector<const
    spu::runtime::Task *> &, const size_t, const bool, const std::vector<size_t>
    &>(), "firsts"_a, "lasts"_a, "exclusions"_a, "n_threads"_a = 1,
    "thread_pinning"_a = false, "puids"_a = std::vector<size_t>());
    sequence_class.def(py::init<const std::vector<spu::runtime::Task *> &, const
    size_t, const bool, const std::vector<size_t> &, const bool>(), "firsts"_a,
    "n_threads"_a = 1, "thread_pinning"_a = false, "puids"_a =
    std::vector<size_t>(), "tasks_inplace"_a = true);
    sequence_class.def(py::init<const std::vector<spu::runtime::Task *> &, const
    std::vector<spu::runtime::Task *> &, const size_t, const bool, const
    std::vector<size_t> &, const bool>(), "firsts"_a, "lasts"_a, "n_threads"_a =
    1, "thread_pinning"_a = false, "puids"_a = std::vector<size_t>(),
    "tasks_inplace"_a = true); sequence_class.def(py::init<const
    std::vector<spu::runtime::Task *> &, const std::vector<spu::runtime::Task *>
    &, const std::vector<spu::runtime::Task *> &, const size_t, const bool, const
    std::vector<size_t> &, const bool>(), "firsts"_a, "lasts"_a, "exclusions"_a,
    "n_threads"_a = 1, "thread_pinning"_a = false, "puids"_a =
    std::vector<size_t>(), "tasks_inplace"_a = true);
    sequence_class.def(py::init<spu::runtime::Task &, const size_t, const bool,
    const std::vector<size_t> &, const bool>(), "first"_a, "n_threads"_a = 1,
    "thread_pinning"_a = false, "puids"_a = std::vector<size_t>(),
    "tasks_inplace"_a = true); sequence_class.def(py::init<spu::runtime::Task &,
    spu::runtime::Task &, const size_t, const bool, const std::vector<size_t> &,
    const bool>(), "first"_a, "last"_a, "n_threads"_a = 1, "thread_pinning"_a =
    false, "puids"_a = std::vector<size_t>(), "tasks_inplace"_a = true);*/
    // sequence_class.def("exec", [](spu::runtime::Sequence& self,
    // std::function<bool(const std::vector<const int*>&)>
    // stop_condition){self.exec(stop_condition);});
    sequence_class.def("exec",
                       [](spu::runtime::Sequence& self)
                       {
                           py::gil_scoped_release release{};
                           self.exec();
                       });

    sequence_class.def("exec_n_times",
                       [](spu::runtime::Sequence& self, size_t n_exec = 1)
                       {
                           py::gil_scoped_release release{};
                           std::atomic<size_t> counter(0);
                           self.exec([&counter, n_exec]() { return ++counter >= n_exec; });
                       });

    sequence_class.def("exec",
                       [](spu::runtime::Sequence& self, spu::tools::Terminal_dump& terminal, std::ostream& stats_file)
                       {
                           py::gil_scoped_release release{};
                           self.exec(
                             [&]() -> bool
                             {
                                 py::gil_scoped_acquire gil;
                                 terminal.temp_report(stats_file);
                                 return false;
                             });
                       });

    sequence_class.def("exec_seq",
                       &spu::runtime::Sequence::exec_seq,
                       "tid"_a = 0,
                       "frame_id"_a = -1,
                       py::call_guard<py::gil_scoped_release>());
    sequence_class.def("exec_step",
                       &spu::runtime::Sequence::exec_step,
                       "tid"_a = 0,
                       "frame_id"_a = -1,
                       py::return_value_policy::reference,
                       py::call_guard<py::gil_scoped_release>());

    sequence_class.def("export_dot",
                       [](spu::runtime::Sequence& self, const std::string& file_name)
                       {
                           std::ofstream f(file_name);
                           self.export_dot(f);
                       });

    sequence_class.def(
      "show_stats",
      [](spu::runtime::Sequence& self, const bool ordered = false, const bool display_thr = true)
      {
          py::scoped_ostream_redirect stream(std::cout,                                // std::ostream&
                                             py::module_::import("sys").attr("stdout") // Python output
          );
          spu::tools::Stats::show(self.get_modules_per_types(), ordered, display_thr);
      },
      "ordered"_a = false,
      "display_thr"_a = true);

    sequence_class.def(
      "get_modules_per_threads", &spu::runtime::Sequence::get_modules_per_threads, py::return_value_policy::reference);
    sequence_class.def(
      "get_modules_per_types", &spu::runtime::Sequence::get_modules_per_types, py::return_value_policy::reference);
    sequence_class.def(
      "get_tasks_per_threads", &spu::runtime::Sequence::get_tasks_per_threads, py::return_value_policy::reference);
    sequence_class.def(
      "get_tasks_per_types", &spu::runtime::Sequence::get_tasks_per_types, py::return_value_policy::reference);

    sequence_class.def_property_readonly(
      "last_tasks", &spu::runtime::Sequence::get_lasts_tasks, py::return_value_policy::reference);
    sequence_class.def_property_readonly(
      "first_tasks", &spu::runtime::Sequence::get_firsts_tasks, py::return_value_policy::reference);
    sequence_class.def_property(
      "no_copy_mode", &spu::runtime::Sequence::is_no_copy_mode, &spu::runtime::Sequence::set_no_copy_mode);
};
