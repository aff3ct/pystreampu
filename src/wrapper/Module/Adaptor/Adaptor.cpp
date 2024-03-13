#include "wrapper/Module/Adaptor/Adaptor.hpp"
#include "wrapper/Module/Adaptor/Adaptor_1_to_n.hpp"
#include "wrapper/Module/Adaptor/Adaptor_n_to_1.hpp"

#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/Type/Type.hpp"

namespace py = pybind11;
using namespace pyaf::wrapper;
using namespace py::literals;

void pyaf::wrapper::wrap_adaptor(py::handle scope)
{
    auto py_adaptor_class = py::class_<aff3ct::module::Adaptor, aff3ct::module::Module, aff3ct::tools::Interface_waiting>(scope, "Adaptor");

    py_adaptor_class.def_property_readonly("n_elmts", &aff3ct::module::Adaptor::get_n_elmts);
    py_adaptor_class.def_property_readonly("n_bytes", &aff3ct::module::Adaptor::get_n_bytes);
    py_adaptor_class.def_property_readonly("dtype", [](const aff3ct::module::Adaptor& self){
        return pyaf::dtype::get(pyaf::utils::typeid2str(self.get_datatype()));
    });
    py_adaptor_class.def_property("n_frames", &aff3ct::module::Adaptor::get_n_frames, &aff3ct::module::Adaptor::set_n_frames);
}

void pyaf::wrapper::wrap_adaptors(py::handle scope)
{
    pyaf::wrapper::wrap_adaptor       (scope);
    pyaf::wrapper::wrap_adaptor_1_to_n(scope);
    pyaf::wrapper::wrap_adaptor_n_to_1(scope);
}