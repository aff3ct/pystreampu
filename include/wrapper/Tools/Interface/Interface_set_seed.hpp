#ifndef WRAPPER_INTERFACE_SET_SEED_HPP__
#define WRAPPER_INTERFACE_SET_SEED_HPP__

#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	class py_Interface_set_seed : public aff3ct::tools::Interface_set_seed {
	public:
		/* Trampoline (need one for each virtual function) */
		void set_seed(const int seed) override {
			PYBIND11_OVERRIDE_PURE(
				void,                              /* Return type */
				aff3ct::tools::Interface_set_seed, /* Parent class */
				set_seed                              /* Name of function in C++ (must match Python name) */
			);
		}
	};

	void wrap_interface_set_seed(py::module_ &scope);
}
}

#endif // WRAPPER_INTERFACE_SET_SEED_HPP__