#include "Adder.hpp"

Adder::Adder(const int n_elmts)
  : Stateful()
  , n_elmts(n_elmts)
{
    const std::string name = "Adder";
    this->set_name(name);

    auto& p = this->create_task("add_one");                                                  // Create the task
    size_t ps_input = this->template create_socket_in<double>(p, "input", this->n_elmts);    // Create the input socket
    size_t ps_output = this->template create_socket_out<double>(p, "output", this->n_elmts); // Create the output socket

    // create the codelet
    this->create_codelet(
      p,
      [ps_input, ps_output](spu::module::Module& m, spu::runtime::Task& t, const size_t frame_id) -> int
      {
          // Recover the Module and Sockets in the codelet
          auto& adder = static_cast<Adder&>(m);
          double* input = (double*)(t[ps_input].get_dataptr());
          double* output = (double*)(t[ps_output].get_dataptr());

          // Process the data
          adder.add_one(input, output);
          return spu::runtime::status_t::SUCCESS;
      });
}

// Actual implementation of the task.
void
Adder::add_one(const double* input, double* output) const
{
    for (int i = 0; i < this->n_elmts; i++)
        output[i] = input[i] + 1;
}