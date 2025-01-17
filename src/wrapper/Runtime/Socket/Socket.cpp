#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <typeinfo>

#include "wrapper/Runtime/Socket/Socket.hpp"
#include "wrapper/Common/Tools/Type/Type.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyspu::wrapper;
using namespace spu::runtime;

std::map<std::type_index, std::string> type_map = { { typeid(int8_t), py::format_descriptor<int8_t>::format() },
                                                    { typeid(int16_t), py::format_descriptor<int16_t>::format() },
                                                    { typeid(int32_t), py::format_descriptor<int32_t>::format() },
                                                    { typeid(int64_t), py::format_descriptor<int64_t>::format() },
                                                    { typeid(uint8_t), py::format_descriptor<uint8_t>::format() },
                                                    { typeid(uint16_t), py::format_descriptor<uint16_t>::format() },
                                                    { typeid(uint32_t), py::format_descriptor<uint32_t>::format() },
                                                    { typeid(uint64_t), py::format_descriptor<uint64_t>::format() },
                                                    { typeid(float), py::format_descriptor<float>::format() },
                                                    { typeid(double), py::format_descriptor<double>::format() } };

void
pyspu::wrapper::wrap_socket(py::handle scope)
{
    py::class_<Socket, spu::tools::Interface_reset, spu::runtime::Socket_Publicist> py_socket(
      scope, "Socket", py::buffer_protocol(), py::dynamic_attr());

    py::enum_<socket_t>(py_socket, "directions", "Enumeration of socket directions")
      .value("IN", socket_t::SIN, "Input socket")
      .value("OUT", socket_t::SOUT, "Output socket")
      .value("FWD", socket_t::SFWD, "Forward socket");

    py_socket.def_buffer(
      [](Socket& s) -> py::buffer_info
      {
          if (s.get_dataptr() == nullptr)
              return py::buffer_info(nullptr, s.get_datatype_size(), type_map[s.get_datatype()], 0);

          size_t n_frames = s.get_task().get_module().get_n_frames();
          size_t n_row = n_frames;
          size_t n_col = s.get_n_elmts() / n_frames;

          return py::buffer_info(s.get_dataptr(),            /* Pointer to buffer */
                                 s.get_datatype_size(),      /* Size of one scalar */
                                 type_map[s.get_datatype()], /* Python struct-style format descriptor */
                                 2,                          /* Number of dimensions */
                                 { n_row, n_col },           /* Buffer dimensions */
                                 { (size_t)s.get_datatype_size() * n_col, (size_t)s.get_datatype_size() },
                                 s.get_type() == socket_t::SIN);
      });
    py_socket.def_property_readonly(
      "wave",
      [](const spu::runtime::Socket& self) -> py::array
      {
          if (self.get_dataptr() == nullptr)
              return py::array(py::buffer_info(nullptr, 1, type_map[self.get_datatype()], {}));

          // Use this if the C++ buffer should NOT be deallocated
          // once Python no longer has a reference to it
          py::capsule buffer_handle([]() {});

          size_t n_frames = self.get_task().get_module().get_n_frames();
          size_t n_row = self.get_task().get_module().get_n_frames_per_wave();
          size_t n_col = self.get_n_elmts() / n_frames;

          return py::array(
            py::buffer_info(self.get_dataptr(),            /* Pointer to buffer */
                            self.get_datatype_size(),      /* Size of one scalar */
                            type_map[self.get_datatype()], /* Python struct-style format
                                                              descriptor */
                            2,                             /* Number of dimensions */
                            { n_row, n_col },              /* Buffer dimensions */
                            { (size_t)self.get_datatype_size() * n_col, (size_t)self.get_datatype_size() },
                            self.get_type() == socket_t::SIN),
            buffer_handle);
      });

    py_socket.def_property_readonly("task", &spu::runtime::Socket::get_task, "Task owning the socket.");
    py_socket.def_property_readonly("n_elmts", &spu::runtime::Socket::get_n_elmts, "Number of elements per `n_frames`");
    py_socket.def("get_bound_sockets", &spu::runtime::Socket::get_bound_sockets, "Sockets to wich the socket is bound (for output sockets only).");
    py_socket.def_property_readonly(
      "dtype",
      [](const spu::runtime::Socket& self) { return pyspu::dtype::get(self.get_datatype_string()); },
      "Data type.");
    py_socket.def("get_bound_socket",
    [](const spu::runtime::Socket& self) { return &self.get_bound_socket(); },
    "Socket bound to self (for input sockets only).", py::return_value_policy::reference);

    py_socket.def(
      "has_data",
      [](const spu::runtime::Socket& self) { return self.get_dataptr() != nullptr; },
      "Return True if the socket has data allocated.");
    py_socket.def_property_readonly(
      "dataaddr",
      [](const spu::runtime::Socket& self)
      {
          std::stringstream ss;
          ss << self.get_dataptr();
          return ss.str();
      },
      "Return the socket data address as str.");

    py_socket.def_property_readonly(
      "numpy",
      [](spu::runtime::Socket& self)
      {
          py::array array = py::cast(self);
          return array;
      },
      "Numpy array view of the socket (copy-less).");

    py_socket.def("__bool__",
                  [](const spu::runtime::Socket& sckt)
                  {
                        size_t n_frames = sckt.get_task().get_module().get_n_frames();
                        size_t n = sckt.get_n_elmts() / n_frames;
                        if (n > n_frames)
                        {
                            std::stringstream message;
                            message << "The truth value of an array with more than one element is "
                                        "ambiguous.";
                            throw spu::tools::runtime_error(message.str());
                        }
                        if (sckt.get_datatype() == typeid(int8_t))
                            return (bool)(static_cast<int8_t*>(sckt.get_dataptr())[0]);
                        else if (sckt.get_datatype() == typeid(int16_t))
                            return (bool)(static_cast<int16_t*>(sckt.get_dataptr())[0]);
                        else if (sckt.get_datatype() == typeid(int32_t))
                            return (bool)(static_cast<int32_t*>(sckt.get_dataptr())[0]);
                        else if (sckt.get_datatype() == typeid(int64_t))
                            return (bool)(static_cast<int64_t*>(sckt.get_dataptr())[0]);
                        else if (sckt.get_datatype() == typeid(uint8_t))
                            return (bool)(static_cast<uint8_t*>(sckt.get_dataptr())[0]);
                        else if (sckt.get_datatype() == typeid(uint16_t))
                            return (bool)(static_cast<uint16_t*>(sckt.get_dataptr())[0]);
                        else if (sckt.get_datatype() == typeid(uint32_t))
                            return (bool)(static_cast<uint32_t*>(sckt.get_dataptr())[0]);
                        else if (sckt.get_datatype() == typeid(uint64_t))
                            return (bool)(static_cast<uint64_t*>(sckt.get_dataptr())[0]);
                        else if (sckt.get_datatype() == typeid(float))
                            return (bool)(static_cast<float*>(sckt.get_dataptr())[0]);
                        else if (sckt.get_datatype() == typeid(double))
                            return (bool)(static_cast<double*>(sckt.get_dataptr())[0]);
                        else
                        {
                        std::stringstream message;
                        message << "Unknown socket type '" << sckt.get_datatype_string() << "'.";
                        throw spu::tools::unimplemented_error(message.str());
                        }
                  });

    py_socket.def(
      "_bind",
      [](spu::runtime::Socket& self, spu::runtime::Socket& s_out, const int priority) { self.bind(s_out, priority); },
      "Binds the socket to socket 's_out' with priority 'priority'.",
      "s_out"_a,
      "priority"_a = -1);

    py_socket.def(
      "_bind",
      [](spu::runtime::Socket& self, py::array& arr)
      {
          size_t n_row = (size_t)self.get_task().get_module().get_n_frames();
          size_t n_col = (size_t)self.get_n_elmts() / n_row;

          py::buffer_info buffer = arr.request();

          if (n_row > 1 && buffer.ndim == 2)
          {
              if ((size_t)buffer.shape[0] != n_row || (size_t)buffer.shape[1] != n_col)
              {
                  std::stringstream message;
                  message << "The shape of the array must match the socket one.";
                  message << "Socket shape: " << n_row << " x " << n_col << ".";
                  message << "Array shape: " << buffer.shape[0] << " x " << buffer.shape[1] << ".\n";
                  throw spu::tools::runtime_error(message.str());
              }
          }
          else if (n_row == 1 && buffer.ndim == 1)
          {
              if ((size_t)buffer.shape[0] != n_col)
              {
                  std::stringstream message;
                  message << "The shape of the array must match the socket one.";
                  message << "Socket shape: " << 1 << " x " << n_col << ".";
                  message << "Array shape: " << 1 << " x " << buffer.shape[0] << ".\n";
                  throw spu::tools::runtime_error(message.str());
              }
          }

          py::array py_self = py::cast(self);
          if (!arr.dtype().is(py_self.dtype()))
          {
              std::stringstream message;
              message << "The dtype of the array must match the socket one.\n";
              message << "Socket dtype: " << py_self.dtype().attr("name").cast<std::string>() << ".\n";
              message << "Array dtype: " << arr.dtype().attr("name").cast<std::string>() << ".\n";
              throw spu::tools::runtime_error(message.str());
          }

          self.bind(buffer.ptr);
      },
      "Binds the socket to the numpy array 'array' data.",
      "array"_a);
    py_socket.def_property_readonly("name", &spu::runtime::Socket::get_name);
    py_socket.def_property_readonly("direction", &spu::runtime::Socket::get_type, "Direction of the socket");
};
