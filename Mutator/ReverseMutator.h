#ifndef TABLEOFLIFE_REVERSEMATER_H
#define TABLEOFLIFE_REVERSEMATER_H

#include "IMutator.h"

//реверсит все биты
template <std::size_t N>
class ReverseMutator : public IMutator<N> {
public:
  explicit ReverseMutator(float probability) : probability(probability){};
  ~ReverseMutator() = default;
  Genome<N>* Mutate(Genome<N>*) override;

private:
  float probability;
};

template <std::size_t N>
Genome<N>* ReverseMutator<N>::Mutate(Genome<N>* genome) {
  return genome;
}
#endif // TABLEOFLIFE_REVERSEMATER_H
