#include <pybind11/pybind11.h>
#include <aff3ct-core.hpp>
#include <iostream>
#include <sstream>

#include <string>

namespace py = pybind11;
template<typename T>
std::string display_flag(T flag)
{
    std::stringstream message;
    message << flag;
    return message.str();
}
namespace pyaf
{
    namespace wrapper{


        inline void wrap_rang_flags(py::module_ &m)
        {
            py::enum_<rang::style>(m, "style", py::arithmetic())
                .value("reset",     rang::style::reset)
                .value("bold",      rang::style::bold)
                .value("dim",       rang::style::dim)
                .value("italic",    rang::style::italic)
                .value("underline", rang::style::underline)
                .value("blink",     rang::style::blink)
                .value("rblink",    rang::style::rblink)
                .value("reversed",  rang::style::reversed)
                .value("conceal",   rang::style::conceal)
                .value("crossed",   rang::style::crossed)
                .def("__str__", [](rang::style p) {
                    return display_flag<rang::style>(p);
                }, py::prepend());


            py::enum_<rang::fg>(m, "fg")
                .value("black",   rang::fg::black)
                .value("red",     rang::fg::red)
                .value("green",   rang::fg::green)
                .value("yellow",  rang::fg::yellow)
                .value("blue",    rang::fg::blue)
                .value("magenta", rang::fg::magenta)
                .value("cyan",    rang::fg::cyan)
                .value("gray",    rang::fg::gray)
                .value("reset",   rang::fg::reset)
                .def("__str__", [](rang::fg p) {
                    return display_flag<rang::fg>(p);
                }, py::prepend());

            py::enum_<rang::bg>(m, "bg")
                .value("black",   rang::bg::black)
                .value("red",     rang::bg::red)
                .value("green",   rang::bg::green)
                .value("yellow",  rang::bg::yellow)
                .value("blue",    rang::bg::blue)
                .value("magenta", rang::bg::magenta)
                .value("cyan",    rang::bg::cyan)
                .value("gray",    rang::bg::gray)
                .value("reset",   rang::bg::reset)
                .def("__str__", [](rang::bg p) {
                    return display_flag<rang::bg>(p);
                }, py::prepend());

            py::enum_<rang::fgB>(m, "fgB")
                .value("black",   rang::fgB::black)
                .value("red",     rang::fgB::red)
                .value("green",   rang::fgB::green)
                .value("yellow",  rang::fgB::yellow)
                .value("blue",    rang::fgB::blue)
                .value("magenta", rang::fgB::magenta)
                .value("cyan",    rang::fgB::cyan)
                .value("gray",    rang::fgB::gray)
                .def("__str__", [](rang::fgB p) {
                    return display_flag<rang::fgB>(p);
                }, py::prepend());


            py::enum_<rang::bgB>(m, "bgB")
                .value("black",   rang::bgB::black)
                .value("red",     rang::bgB::red)
                .value("green",   rang::bgB::green)
                .value("yellow",  rang::bgB::yellow)
                .value("blue",    rang::bgB::blue)
                .value("magenta", rang::bgB::magenta)
                .value("cyan",    rang::bgB::cyan)
                .value("gray",    rang::bgB::gray)
                .def("__str__", [](rang::bgB p) {
                    return display_flag<rang::bgB>(p);
                }, py::prepend());

            py::enum_<rang::control>(m, "control")
                .value("Off",     rang::control::Off)
                .value("Auto",    rang::control::Auto)
                .value("Force",   rang::control::Force);

            py::enum_<rang::winTerm>(m, "winTerm")
                .value("Auto",     rang::winTerm::Auto)
                .value("Ansi",    rang::winTerm::Ansi)
                .value("Native",   rang::winTerm::Native);

        m.def("setWinTermMode", &rang::setWinTermMode);
        m.def("setControlMode", &rang::setControlMode);

    	m.def("enable_colors", [](){setControlMode(rang::control::Force);});
	    m.def("disable_colors",[](){setControlMode(rang::control::Off);});

        }
}
}