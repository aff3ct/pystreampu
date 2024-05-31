#ifndef WRAPPER_INTERFACE_TERMINAL_HPP__
#define WRAPPER_INTERFACE_TERMINAL_HPP__

#include <pybind11/pybind11.h>
#include <streampu.hpp>

namespace py = pybind11;

namespace pyspu
{
namespace wrapper
{
class py_Terminal : spu::tools::Terminal
{
  public:
    /* Trampoline (need one for each virtual function) */
    void legend(std::ostream& stream = std::cout) const override
    {
        PYBIND11_OVERRIDE_PURE(void,                 /* Return type */
                               spu::tools::Terminal, /* Parent class */
                               legend,               /* Name of function in C++ (must match Python name) */
                               stream);
    }
    void report(std::ostream& stream = std::cout, bool final = false) override
    {
        PYBIND11_OVERRIDE_PURE(void,                 /* Return type */
                               spu::tools::Terminal, /* Parent class */
                               report,               /* Name of function in C++ (must match Python name) */
                               stream,
                               final);
    }
};

class Publicist_Terminal : public spu::tools::Terminal
{
  public:
    using Terminal::report;
};

void
wrap_terminal(py::module_& scope);
} // namespace wrapper
} // namespace pyspu

#endif // WRAPPER_INTERFACE_TERMINAL_HPP__