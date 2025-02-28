#ifndef ADDER_HPP_
#define ADDER_HPP_

#include <streampu.hpp>

class Adder : public spu::module::Stateful
{
  protected:
    int n_elmts;

  public:
    Adder(const int n_elmts);
    virtual ~Adder() = default;

    void add_one(const double* input, double* output) const;
};

#endif // ADDER_HPP_