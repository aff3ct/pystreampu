#include "wrapper/Module/Adaptor/Adaptor.hpp"
#include "wrapper/Module/Adaptor/Adaptor_1_to_n.hpp"
#include "wrapper/Module/Adaptor/Adaptor_n_to_1.hpp"

#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_functions.h"

namespace py = pybind11;
using namespace pyspu::wrapper;
using namespace py::literals;

void
pyspu::wrapper::wrap_adaptor(py::handle scope)
{
    auto py_adaptor_class =
      py::class_<spu::module::Adaptor, spu::module::Module, spu::tools::Interface_waiting>(scope, "Adaptor");

    py_adaptor_class.def_property_readonly("n_elmts", &spu::module::Adaptor::get_n_elmts);
    py_adaptor_class.def_property_readonly("n_bytes", &spu::module::Adaptor::get_n_bytes);
    py_adaptor_class.def_property_readonly("dtype",
                                           [](const spu::module::Adaptor& self)
                                           { return pyspu::dtype::get(pyspu::utils::typeid2str(self.get_datatype())); });
    py_adaptor_class.def_property("n_frames", &spu::module::Adaptor::get_n_frames, &spu::module::Adaptor::set_n_frames);
}

void
pyspu::wrapper::wrap_adaptors(py::handle scope)
{
    pyspu::wrapper::wrap_adaptor(scope);
    pyspu::wrapper::wrap_adaptor_1_to_n(scope);
    pyspu::wrapper::wrap_adaptor_n_to_1(scope);
}