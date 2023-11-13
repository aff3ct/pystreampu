#ifndef WRAPPER_INTERFACE_CLONE_HPP__
#define WRAPPER_INTERFACE_CLONE_HPP__

#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	class py_Interface_clone : public aff3ct::tools::Interface_clone {
	public:
		/* Trampoline (need one for each virtual function) */
		aff3ct::tools::Interface_clone* clone() const override {
			PYBIND11_OVERRIDE(
				aff3ct::tools::Interface_clone*, /* Return type */
				aff3ct::tools::Interface_clone,  /* Parent class */
				clone                            /* Name of function in C++ (must match Python name) */
			);
		}
	};

	void wrap_interface_clone(py::module_ &scope);
}
}

#endif // WRAPPER_INTERFACE_CLONE_HPP__