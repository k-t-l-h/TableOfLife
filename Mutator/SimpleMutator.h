#ifndef TABLEOFLIFE_SIMPLEMUTATOR_H
#define TABLEOFLIFE_SIMPLEMUTATOR_H
#include "IMutator.h"

template <std::size_t N>
class SimpleMutator : public IMutator<N> {
public:
  explicit SimpleMutator(float probability) : probability(probability){};
  ~SimpleMutator() = default;
  Genome<N>* Mutate(Genome<N>*) override;

private:
  float probability;
};

template <std::size_t N>
Genome<N>* SimpleMutator<N>::Mutate(Genome<N>* genome) {
  return genome;
}
#endif  // TABLEOFLIFE_SIMPLEMUTATOR_H
