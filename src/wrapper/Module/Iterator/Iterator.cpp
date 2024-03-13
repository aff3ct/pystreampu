#include "wrapper/Module/Iterator/Iterator.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;
using namespace py::literals;

void pyaf::wrapper::wrap_iterator(py::handle scope)
{
    auto doc_str = R"pbdoc()pbdoc";
    auto py_iterator_class = py::class_<aff3ct::module::Iterator, aff3ct::module::Module, aff3ct::tools::Interface_reset>(scope, "Iterator");
    py_iterator_class.def(py::init<const size_t>(), "limit"_a, doc_str, py::return_value_policy::take_ownership);
    py_iterator_class.def_property("limit", &aff3ct::module::Iterator::get_limit, &aff3ct::module::Iterator::set_limit);
}