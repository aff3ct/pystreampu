#include "wrapper/Module/Slicer/Slicer.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace aff3ct;
using namespace aff3ct::module;
using namespace aff3ct::tools;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_slicer(py::handle scope)
{
	auto slicer_class = py::class_<aff3ct::module::Slicer,aff3ct::module::Module>(scope, "Slicer");
	slicer_class.def(py::init<aff3ct::runtime::Socket&, const std::vector<int>&>(),"sck"_a, "slice"_a, R"pbdoc(Range:)pbdoc", py::return_value_policy::take_ownership);
	slicer_class.def(py::init<aff3ct::runtime::Socket&, const int>(),"sck"_a, "idx"_a, R"pbdoc(Range:)pbdoc", py::return_value_policy::take_ownership);
}

Slicer
::Slicer(aff3ct::runtime::Socket& sck, const std::vector<int>& slice)
: Module(), n_elmts(sck.get_n_elmts()/sck.get_task().get_module().get_n_frames()), slice(slice)
{
	const std::string name = "Slicer";
	this->set_name(name);

	this->task_init(sck);

	this->set_n_frames(sck.get_task().get_module().get_n_frames());
}

Slicer
::Slicer(aff3ct::runtime::Socket& sck, const int idx)
: Slicer(sck, std::vector<int>(1,idx))
{
}

void Slicer
::task_init(aff3ct::runtime::Socket& sck)
{
		 if (sck.get_datatype() == typeid(int8_t  )) this->_task_init<int8_t  >();
	else if (sck.get_datatype() == typeid(int16_t )) this->_task_init<int16_t >();
	else if (sck.get_datatype() == typeid(int32_t )) this->_task_init<int32_t >();
	else if (sck.get_datatype() == typeid(int64_t )) this->_task_init<int64_t >();
	else if (sck.get_datatype() == typeid(uint8_t )) this->_task_init<uint8_t >();
	else if (sck.get_datatype() == typeid(uint16_t)) this->_task_init<uint16_t>();
	else if (sck.get_datatype() == typeid(uint32_t)) this->_task_init<uint32_t>();
	else if (sck.get_datatype() == typeid(uint64_t)) this->_task_init<uint64_t>();
	else if (sck.get_datatype() == typeid(float   )) this->_task_init<float   >();
	else if (sck.get_datatype() == typeid(double  )) this->_task_init<double  >();
	else
	{
		std::stringstream message;
		message << "Unhandled socket type '" << sck.get_datatype_string() << "'.";
		throw std::runtime_error(message.str());
	}
}

Slicer* Slicer
::clone() const
{
	auto m = new Slicer(*this);
	m->deep_copy(*this);
	return m;
}