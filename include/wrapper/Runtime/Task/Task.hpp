#ifndef BIND_TASK_HPP_
#define BIND_TASK_HPP_

#include <aff3ct-core.hpp>
#include <pybind11/pybind11.h>
#include <memory>
#include "wrapper/Common/Wrapper_py/Wrapper_py.hpp"

namespace py = pybind11;

/*namespace aff3ct
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
	void wrap_task(py::handle scope);
}
}


#endif //BIND_TASK_HPP_