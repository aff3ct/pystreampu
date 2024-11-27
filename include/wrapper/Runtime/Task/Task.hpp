#ifndef BIND_TASK_HPP_
#define BIND_TASK_HPP_

#include <memory>

#include "wrapper/Common/pybind11_common.h"

#include <streampu.hpp>

namespace py = pybind11;

/*namespace spu
{
namespace runtime
{
class Task_Publicist : public Task
{
        public:
        using Task::Task;
        using Task::codelet;

        virtual ~Task_Publicist() = default;
};
}
}*/

namespace pyspu
{
namespace wrapper
{
void
wrap_task(py::handle scope);
}
} // namespace pyspu

#endif // BIND_TASK_HPP_