#ifndef BIND_TASK_HPP_
#define BIND_TASK_HPP_

#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"
#include <memory>
#include <pybind11/pybind11.h>
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

namespace pyaf
{
namespace wrapper
{
void
wrap_task(py::handle scope);
}
} // namespace pyaf

#endif // BIND_TASK_HPP_