#ifndef WRAPPER_PY_HPP_
#define WRAPPER_PY_HPP_

#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyaf
{
namespace wrapper
{
class Wrapper_py
{
  public:
    Wrapper_py();
    virtual void definitions();
    virtual ~Wrapper_py() = default;
};
} // namespace wrapper
} // namespace pyaf

#endif