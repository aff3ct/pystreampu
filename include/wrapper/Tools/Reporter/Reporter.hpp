#ifndef WRAPPER_INTERFACE_REPORTER_HPP__
#define WRAPPER_INTERFACE_REPORTER_HPP__

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>
#include <string>

#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	class py_Reporter : aff3ct::tools::Reporter{
	public:
		//using aff3ct::tools::Reporter::Reporter;

		/* Trampoline (need one for each virtual function) */
		aff3ct::tools::Reporter::report_t report(bool final = false) override {
			PYBIND11_OVERRIDE_PURE(
				aff3ct::tools::Reporter::report_t, /* Return type */
				aff3ct::tools::Reporter,           /* Parent class */
				report,                             /* Name of function in C++ (must match Python name) */
				final
			);
		}
	};

	void wrap_reporter(py::module_ &scope);
}
}

#endif // WRAPPER_INTERFACE_REPORTER_HPP__