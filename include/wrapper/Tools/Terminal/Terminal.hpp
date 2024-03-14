#ifndef WRAPPER_INTERFACE_TERMINAL_HPP__
#define WRAPPER_INTERFACE_TERMINAL_HPP__

#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>

namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
	class py_Terminal : aff3ct::tools::Terminal{
	public:
		/* Trampoline (need one for each virtual function) */
		void legend(std::ostream &stream = std::cout) const override {
			PYBIND11_OVERRIDE_PURE(
				void,                     /* Return type */
				aff3ct::tools::Terminal,  /* Parent class */
				legend,                    /* Name of function in C++ (must match Python name) */
				stream
			);
		}
		void report(std::ostream &stream = std::cout, bool final = false) override {
			PYBIND11_OVERRIDE_PURE(
				void,                     /* Return type */
				aff3ct::tools::Terminal,  /* Parent class */
				report,                    /* Name of function in C++ (must match Python name) */
				stream,
				final
			);
		}
	};

	class Publicist_Terminal : public aff3ct::tools::Terminal {
	public:
		using Terminal::report;
	};


	void wrap_terminal(py::module_ &scope);
}
}

#endif // WRAPPER_INTERFACE_TERMINAL_HPP__