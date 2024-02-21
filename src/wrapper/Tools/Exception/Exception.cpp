#include "wrapper/Tools/Exception/Exception.hpp"

namespace py = pybind11;
using namespace py::literals;
using namespace pyaf::wrapper;

void pyaf::wrapper::wrap_exceptions(py::module_& scope)
{
	py::register_exception<aff3ct::tools::cannot_allocate    >(scope, "CannotAllocate"    );
	py::register_exception<aff3ct::tools::control_flow_error >(scope, "ControlFlowError"  );
	py::register_exception<aff3ct::tools::domain_error       >(scope, "DomainError"       );
	py::register_exception<aff3ct::tools::invalid_argument   >(scope, "InvalidArgument"   );
	py::register_exception<aff3ct::tools::length_error       >(scope, "LengthError"       );
	py::register_exception<aff3ct::tools::logic_error        >(scope, "LogicError"        );
	py::register_exception<aff3ct::tools::out_of_range       >(scope, "OutOfRange"        );
	py::register_exception<aff3ct::tools::overflow_error     >(scope, "OverflowError"     );
	py::register_exception<aff3ct::tools::processing_aborted >(scope, "ProcessingAborted" );
	py::register_exception<aff3ct::tools::range_error        >(scope, "RangeError"        );
	py::register_exception<aff3ct::tools::runtime_error      >(scope, "RuntimeError"      );
	py::register_exception<aff3ct::tools::underflow_error    >(scope, "UnderflowError"    );
	py::register_exception<aff3ct::tools::unimplemented_error>(scope, "UnimplementedError");
	py::register_exception<aff3ct::tools::waiting_canceled   >(scope, "WaitingCanceled"   );
}