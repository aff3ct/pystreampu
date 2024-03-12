#include <pybind11/pybind11.h>
#include <iostream>

namespace pyaf
{
    enum class fmtflags{
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
		uppercase = std::ios_base::	uppercase
    };

    inline fmtflags operator|(fmtflags a, fmtflags b)
    {
        return static_cast<fmtflags>(static_cast<std::ios_base::fmtflags>(a) | static_cast<std::ios_base::fmtflags>(b));
    }
    namespace wrapper{
        inline void wrap_fmtflags(py::module_ &m)
        {
            py::enum_<fmtflags>(m, "fmtflags", py::arithmetic())
                .value("dec", pyaf::fmtflags::dec)
                .value("oct", pyaf::fmtflags::oct)
                .value("hex", pyaf::fmtflags::hex)
                .value("basefield", pyaf::fmtflags::basefield)
                .value("left", pyaf::fmtflags::left)
                .value("right", pyaf::fmtflags::right)
                .value("internal", pyaf::fmtflags::internal)
                .value("adjustfield", pyaf::fmtflags::adjustfield)
                .value("scientific", pyaf::fmtflags::scientific)
                .value("fixed", pyaf::fmtflags::fixed)
                .value("floatfield", pyaf::fmtflags::floatfield)
                .value("boolalpha", pyaf::fmtflags::boolalpha)
                .value("showbase", pyaf::fmtflags::showbase)
                .value("showpoint", pyaf::fmtflags::showpoint)
                .value("showpos", pyaf::fmtflags::showpos)
                .value("skipws", pyaf::fmtflags::skipws)
                .value("unitbuf", pyaf::fmtflags::unitbuf)
                .value("uppercase", pyaf::fmtflags::uppercase);
        }
    }
}
