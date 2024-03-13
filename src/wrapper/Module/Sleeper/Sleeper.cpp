#include "wrapper/Module/Sleeper/Sleeper.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;
using namespace py::literals;

void pyaf::wrapper::wrap_sleeper(py::handle scope)
{
    auto doc_str = R"pbdoc()pbdoc";
    auto py_sleeper_class = py::class_<aff3ct::module::Sleeper, aff3ct::module::Module>(scope, "Sleeper");

    py_sleeper_class.def(py::init<const size_t>(), "ns"_a = 0, doc_str, py::return_value_policy::take_ownership);
    py_sleeper_class.def_property("ns", &aff3ct::module::Sleeper::get_ns, &aff3ct::module::Sleeper::set_ns);
}