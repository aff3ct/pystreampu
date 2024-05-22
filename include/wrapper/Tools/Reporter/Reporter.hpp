#ifndef WRAPPER_INTERFACE_REPORTER_HPP__
#define WRAPPER_INTERFACE_REPORTER_HPP__

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>
#include <string>

#include <streampu.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	class py_Reporter : spu::tools::Reporter{
	public:
		//using spu::tools::Reporter::Reporter;

		/* Trampoline (need one for each virtual function) */
		spu::tools::Reporter::report_t report(bool final = false) override {
			PYBIND11_OVERRIDE_PURE(
				spu::tools::Reporter::report_t, /* Return type */
				spu::tools::Reporter,           /* Parent class */
				report,                             /* Name of function in C++ (must match Python name) */
				final
			);
		}
	};

	void wrap_reporter(py::module_ &scope);
}
}

#endif // WRAPPER_INTERFACE_REPORTER_HPP__