#ifndef Wrapper_Slicer_HPP_
#define Wrapper_Slicer_HPP_

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>

#include "wrapper/Common/Tools/Type/Type.hpp"
#include <streampu.hpp>
#include <vector>

namespace py = pybind11;
using namespace spu;
using namespace spu::module;
using namespace spu::tools;

namespace spu
{
namespace module
{
class Slicer : public Module
{
  protected:
    int n_elmts;
    bool single_value;
    std::vector<int> slice;

  public:
    Slicer(spu::runtime::Socket& sck, const std::vector<int>& slice);
    Slicer(spu::runtime::Socket& sck, const int idx);

    virtual ~Slicer() = default;
    virtual Slicer* clone() const;

  private:
    void task_init(spu::runtime::Socket& sck);

    template<typename T>
    void _task_init();
};
} // namespace module
} // namespace spu

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "wrapper/Module/Slicer/Slicer.hxx"
#endif

namespace pyspu
{
namespace wrapper
{
void
wrap_slicer(py::handle scope);
}
} // namespace pyspu
#endif // Wrapper_Slicer_HPP_