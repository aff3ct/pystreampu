#include "wrapper/Module/Range/Range.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace spu;
using namespace spu::module;
using namespace spu::tools;
using namespace pyspu::wrapper;

void
pyspu::wrapper::wrap_range(py::handle scope)
{
    auto range_class = py::class_<spu::module::Range, spu::module::Module>(scope, "Range");
    range_class.def(py::init<int, int, int, pyspu::dtype>(),
                    "stop"_a,
                    "start"_a = 0,
                    "step"_a = 1,
                    "dtype"_a = pyspu::dtype::of<int32_t>(),
                    R"pbdoc(Range:)pbdoc",
                    py::return_value_policy::take_ownership);
    range_class.def(
      "__iter__",
      [](Range& self)
      {
          self.set_it(self.get_start());
          return self;
      },
      py::keep_alive<0, 1>());

    range_class.def("__next__",
                    [](Range& self)
                    {
                        self.tasks[0]->exec();
                        return self.tasks[0]->sockets[0];
                    });

    range_class.def_property("throw_to_stop", &Range::get_throw_to_stop, &Range::set_throw_to_stop);
}

Range ::Range(int stop, int start, int step, pyspu::dtype dtype)
  : Module()
  , stop(stop)
  , start(start)
  , step(step)
  , it(0)
  , throw_to_stop(true)
{
    const std::string name = "Range";
    this->set_name(name);

    if (dtype.get_name() == pyspu::dtype::of<int8_t>().get_name())
        this->task_init<int8_t>();
    else if (dtype.get_name() == pyspu::dtype::of<int16_t>().get_name())
        this->task_init<int16_t>();
    else if (dtype.get_name() == pyspu::dtype::of<int32_t>().get_name())
        this->task_init<int32_t>();
    else if (dtype.get_name() == pyspu::dtype::of<int64_t>().get_name())
        this->task_init<int64_t>();
    else if (dtype.get_name() == pyspu::dtype::of<uint8_t>().get_name())
        this->task_init<uint8_t>();
    else if (dtype.get_name() == pyspu::dtype::of<uint16_t>().get_name())
        this->task_init<uint16_t>();
    else if (dtype.get_name() == pyspu::dtype::of<uint32_t>().get_name())
        this->task_init<uint32_t>();
    else if (dtype.get_name() == pyspu::dtype::of<uint64_t>().get_name())
        this->task_init<uint64_t>();
    else if (dtype.get_name() == pyspu::dtype::of<float>().get_name())
        this->task_init<float>();
    else if (dtype.get_name() == pyspu::dtype::of<double>().get_name())
        this->task_init<double>();
    else
    {
        std::stringstream message;
        message << "Unhandled socket type '" << dtype.get_name() << "'.";
        throw spu::tools::unimplemented_error(message.str());
    }
}

Range*
Range ::clone() const
{
    auto m = new Range(*this);
    m->deep_copy(*this);
    return m;
}

void
Range ::set_it(int it)
{
    this->it = it;
}

int
Range ::get_start() const
{
    return this->start;
}

bool
Range ::get_throw_to_stop() const
{
    return this->throw_to_stop;
}

void
Range ::set_throw_to_stop(bool _throw_to_stop)
{
    this->throw_to_stop = _throw_to_stop;
}