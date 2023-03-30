#ifndef WRAPPER_INTERFACE_IS_DONE_HPP__
#define WRAPPER_INTERFACE_IS_DONE_HPP__

#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	class py_Interface_is_done : public aff3ct::tools::Interface_is_done {
	public:
		/* Trampoline (need one for each virtual function) */
		bool is_done() const override {
			PYBIND11_OVERRIDE_PURE(
				bool,                              /* Return type */
				aff3ct::tools::Interface_is_done,  /* Parent class */
				is_done                            /* Name of function in C++ (must match Python name) */
			);
		};
	};

	void wrap_interface_is_done(py::module_ &scope);
}
}

#endif // WRAPPER_INTERFACE_IS_DONE_HPP__