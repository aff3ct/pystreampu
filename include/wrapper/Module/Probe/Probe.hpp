#ifndef WRAPPER_PROBE_HPP_
#define WRAPPER_PROBE_HPP_

#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	//std::type_index get_datatype() const = 0;
	template <typename T = uint8_t>
	class py_Probe : aff3ct::module::Probe<T>{
	public:
		using aff3ct::module::Probe<T>::Probe;

		/* Trampoline (need one for each virtual function) */
		std::type_index get_datatype() const override {
			PYBIND11_OVERRIDE_PURE(
				std::type_index,       /* Return type */
				aff3ct::module::Probe<T>, /* Parent class */
				get_datatype           /* Name of function in C++ (must match Python name) */
			);
		}
	};

	void wrap_probe(py::handle scope);
}
}

#endif //WRAPPER_PROBE_HPP_