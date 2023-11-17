#include "wrapper/Module/Array/Array.hpp"

#include "wrapper/Module/Array/Array.hpp"
#include <string>
namespace py = pybind11;
using namespace py::literals;
using namespace aff3ct::module;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_array(py::module_ &scope)
{
	using lTI = tl::type_list<ALL_DTYPES>;
	lTI::for_each([&](auto ti) {
		using TI = typename decltype(ti)::type;
		std::string TI_str = aff3ct::runtime::type_to_string[typeid(TI)];
		auto arra_py_class = py::class_<aff3ct::module::Array<TI>, aff3ct::module::Module>(scope, std::string("Array_" + TI_str).c_str());

		arra_py_class.def(py::init<int, TI>(),"sz"_a, "val"_a, R"pbdoc()pbdoc", py::return_value_policy::take_ownership);
		arra_py_class.def(py::init<const std::vector<TI>&>(),"frame"_a, R"pbdoc()pbdoc", py::return_value_policy::take_ownership, py::keep_alive<0,2>());
		arra_py_class.def(py::init<const std::vector<std::vector<TI>>&>(),"frames"_a, R"pbdoc()pbdoc", py::return_value_policy::take_ownership, py::keep_alive<0,2>());
	});
}

template <typename T>
Array<T>
::Array(const int sz, const T val)
: Array<T>(std::vector<T>(sz,val))
{
}

template <typename T>
Array<T>
::Array(const std::vector<T>& vec)
: Array<T>(std::vector<std::vector<T>>(1, vec))
{
}

template <typename T>
Array<T>
::Array(const std::vector<std::vector<T>>& vec)
: Module(), data(vec)
{
	const std::string name = "Array";
	this->set_name(name);
	this->set_n_frames(vec.size());

	auto &p = this->create_task("get");
	auto ps_x = this->template create_socket_out<T>(p, "X", vec[0].size());

	auto offset = 0;
	for (auto i = 0; i<vec.size(); i++)
	{
		auto frame_bytes = this->data[i].size()*sizeof(T);
		std::copy((int8_t*)this->data[i].data(),
		          (int8_t*)this->data[i].data() + frame_bytes,
				  (int8_t*)p[ps_x].get_dataptr() + offset);
		offset += frame_bytes;
	}

	this->create_codelet(p, [](Module &m, runtime::Task &t, const size_t frame_id) -> int
	{
		return runtime::status_t::SUCCESS;
	});
}


template <typename T>
Array<T>* Array<T>
::clone() const
{
	auto m = new Array<T>(*this);
	m->deep_copy(*this);
	return m;
}

template class aff3ct::module::Array<int8_t>;
template class aff3ct::module::Array<uint8_t>;
template class aff3ct::module::Array<int16_t>;
template class aff3ct::module::Array<uint16_t>;
template class aff3ct::module::Array<int32_t>;
template class aff3ct::module::Array<uint32_t>;
template class aff3ct::module::Array<int64_t>;
template class aff3ct::module::Array<uint64_t>;
template class aff3ct::module::Array<float>;
template class aff3ct::module::Array<double>;