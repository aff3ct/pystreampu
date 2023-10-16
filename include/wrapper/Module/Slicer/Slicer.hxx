#include "wrapper/Module/Slicer/Slicer.hpp"

namespace py = pybind11;
using namespace aff3ct;
using namespace aff3ct::module;
using namespace aff3ct::tools;

namespace aff3ct
{
namespace module
{
	template<typename T>
	void Slicer
	::_task_init()
	{


		auto &p = this->create_task("write");
		size_t ps_x  = this->template create_socket_fwd<T>(p,  "x", this->n_elmts    );
		size_t ps_nx = this->template create_socket_in <T>(p, "nx", this->slice.size());

		this->create_codelet(p, [ps_x, ps_nx](aff3ct::module::Module &m, aff3ct::runtime::Task &t, const size_t frame_id) -> int
		{
			auto &slicer = static_cast<Slicer&>(m);
			T* x   = (T*)(t[ps_x ].get_dataptr());
			T* nx  = (T*)(t[ps_nx].get_dataptr());

			for (int i = 0; i < slicer.slice.size(); i++)
				x[slicer.slice[i]] = nx[i];

			return runtime::status_t::SUCCESS;
		});

		auto &p1 = this->create_task("write_one");
		size_t p1s_x  = this->template create_socket_fwd<T>(p1,  "x", this->n_elmts);
		size_t p1s_nx = this->template create_socket_in <T>(p1, "nx", 1            );

		this->create_codelet(p1, [p1s_x, p1s_nx](aff3ct::module::Module &m, aff3ct::runtime::Task &t, const size_t frame_id) -> int
		{
			auto &slicer = static_cast<Slicer&>(m);
			T* x   = (T*)(t[p1s_x ].get_dataptr());
			T* nx  = (T*)(t[p1s_nx].get_dataptr());

			for (int i = 0; i < slicer.slice.size(); i++)
				x[slicer.slice[i]] = nx[0];

			return runtime::status_t::SUCCESS;
		});

		auto &p2 = this->create_task("read");

		size_t p2s_x  = this->template create_socket_fwd<T>(p2,  "x", this->n_elmts    );
		size_t p2s_xs = this->template create_socket_out<T>(p2, "xs", this->slice.size());

		this->create_codelet(p2, [p2s_x, p2s_xs](aff3ct::module::Module &m, aff3ct::runtime::Task &t, const size_t frame_id) -> int
		{
			auto &slicer = static_cast<Slicer&>(m);
			T* x   = (T*)(t[p2s_x ].get_dataptr());
			T* xs  = (T*)(t[p2s_xs].get_dataptr());

			for (int i = 0; i < slicer.slice.size(); i++)
				xs[i] = x[slicer.slice[i]];

			return runtime::status_t::SUCCESS;
		});



	}
};
}