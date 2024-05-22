#ifndef Wrapper_Range_HPP_
#define Wrapper_Range_HPP_

#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "wrapper/Common/Tools/Type/Type.hpp"
#include <streampu.hpp>

namespace py = pybind11;
using namespace spu;
using namespace spu::module;
using namespace spu::tools;

namespace spu {
namespace module {
class Range : public Module {
protected:
  int stop;
  int start;
  int step;
  int it;
  bool throw_to_stop;

public:
  Range(int stop, int start = 0, int step = 1,
        pyaf::dtype dtype = pyaf::dtype::of<float>());

  virtual ~Range() = default;
  virtual Range *clone() const;

  void set_it(int it);
  int get_start() const;
  bool get_throw_to_stop() const;
  void set_throw_to_stop(bool _throw_to_stop);

  template <typename T> void task_init();
};
} // namespace module
} // namespace spu

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "wrapper/Module/Range/Range.hxx"
#endif

namespace pyaf {
namespace wrapper {
void wrap_range(py::handle scope);
}
} // namespace pyaf
#endif // Wrapper_Range_HPP_