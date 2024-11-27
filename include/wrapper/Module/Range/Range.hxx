#ifndef WRAPPER_RANGE_HXX_
#define WRAPPER_RANGE_HXX_
#include "wrapper/Module/Range/Range.hpp"

namespace py = pybind11;
using namespace spu;
using namespace spu::module;
using namespace spu::tools;

namespace spu
{
namespace module
{
template<typename T>
void
Range ::task_init()
{
    auto& p = this->create_task("iterate");

    size_t ps_it = this->template create_socket_out<T>(p, "it", 1);
    size_t ps_flg = this->template create_socket_out<int8_t>(p, "flg", 1);

    this->create_codelet(p,
                         [ps_it, ps_flg](spu::module::Module& m, spu::runtime::Task& t, const size_t frame_id) -> int
                         {
                             auto& range = static_cast<Range&>(m);
                             T* it_ = (T*)(t[ps_it].get_dataptr());
                             int8_t* flg_ = (int8_t*)(t[ps_flg].get_dataptr());
                             if (range.it < range.stop)
                             {
                                 *it_ = range.it;
                                 *flg_ = 0;
                                 range.it += range.step;
                             }
                             else
                             {
                                 range.it = range.start;
                                 *flg_ = 1;
                                 if (range.throw_to_stop) throw(py::stop_iteration());
                             }

                             return runtime::status_t::SUCCESS;
                         });
}
}; // namespace module
} // namespace spu

#endif // WRAPPER_RANGE_HXX_