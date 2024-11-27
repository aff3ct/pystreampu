#ifndef Wrapper_Array_HPP_
#define Wrapper_Array_HPP_

#include "wrapper/Common/pybind11_common.h"

#include "wrapper/Common/Tools/Type/Type.hpp"
#include "wrapper/Common/Tools/type_functions.h"
#include "wrapper/Common/Tools/type_list.hpp"
#include <streampu.hpp>
#include <vector>

using namespace spu::module;
namespace py = pybind11;

namespace spu
{
namespace module
{
template<typename T = int>
class Array : public Module
{
  private:
    void* dataptr;

  public:
    Array(py::array_t<T>& data);
    virtual ~Array() = default;
    virtual Array* clone() const;

    void* get_dataptr() const;
};
} // namespace module
} // namespace spu

namespace pyspu
{
namespace wrapper
{
void
wrap_array(py::module_& scope);
}
} // namespace pyspu

#endif // Wrapper_Array_HPP_