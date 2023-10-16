#ifndef Wrapper_Slicer_HPP_
#define Wrapper_Slicer_HPP_

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>

#include <vector>
#include <aff3ct-core.hpp>
#include "wrapper/Common/Tools/Type/Type.hpp"


namespace py = pybind11;
using namespace aff3ct;
using namespace aff3ct::module;
using namespace aff3ct::tools;

namespace aff3ct
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
	Slicer(aff3ct::runtime::Socket& sck, const std::vector<int>& slice);
	Slicer(aff3ct::runtime::Socket& sck, const int idx);

	virtual ~Slicer() = default;
	virtual Slicer* clone() const;

private:
	void task_init(aff3ct::runtime::Socket& sck);

	template<typename T>
	void _task_init();

};
}
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "wrapper/Module/Slicer/Slicer.hxx"
#endif

namespace pyaf
{
namespace wrapper
{
void wrap_slicer(py::handle scope);
}
}
#endif //Wrapper_Slicer_HPP_