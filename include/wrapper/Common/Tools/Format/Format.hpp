#include <iostream>
#include "wrapper/Common/pybind11_common.h"

namespace pyspu
{
enum class fmtflags
{
    dec = std::ios_base::dec,
    oct = std::ios_base::oct,
    hex = std::ios_base::hex,
    basefield = std::ios_base::dec | std::ios_base::oct | std::ios_base::hex,
    left = std::ios_base::left,
    right = std::ios_base::right,
    internal = std::ios_base::internal,
    adjustfield = std::ios_base::left | std::ios_base::right | std::ios_base::internal,
    scientific = std::ios_base::scientific,
    fixed = std::ios_base::fixed,
    floatfield = std::ios_base::scientific | std::ios_base::fixed,
    boolalpha = std::ios_base::boolalpha,
    showbase = std::ios_base::showbase,
    showpoint = std::ios_base::showpoint,
    showpos = std::ios_base::showpos,
    skipws = std::ios_base::skipws,
    unitbuf = std::ios_base::unitbuf,
    uppercase = std::ios_base::uppercase
};

inline fmtflags
operator|(fmtflags a, fmtflags b)
{
    return static_cast<fmtflags>(static_cast<std::ios_base::fmtflags>(a) | static_cast<std::ios_base::fmtflags>(b));
}
namespace wrapper
{
inline void
wrap_fmtflags(py::module_& m)
{
    py::enum_<fmtflags>(m, "FormatFlags", py::arithmetic())
      .value("dec", pyspu::fmtflags::dec)
      .value("oct", pyspu::fmtflags::oct)
      .value("hex", pyspu::fmtflags::hex)
      .value("basefield", pyspu::fmtflags::basefield)
      .value("left", pyspu::fmtflags::left)
      .value("right", pyspu::fmtflags::right)
      .value("internal", pyspu::fmtflags::internal)
      .value("adjustfield", pyspu::fmtflags::adjustfield)
      .value("scientific", pyspu::fmtflags::scientific)
      .value("fixed", pyspu::fmtflags::fixed)
      .value("floatfield", pyspu::fmtflags::floatfield)
      .value("boolalpha", pyspu::fmtflags::boolalpha)
      .value("showbase", pyspu::fmtflags::showbase)
      .value("showpoint", pyspu::fmtflags::showpoint)
      .value("showpos", pyspu::fmtflags::showpos)
      .value("skipws", pyspu::fmtflags::skipws)
      .value("unitbuf", pyspu::fmtflags::unitbuf)
      .value("uppercase", pyspu::fmtflags::uppercase);
}
} // namespace wrapper
} // namespace pyspu
