#ifndef TABLEOFLIFE_SIMPLEMATER_H
#define TABLEOFLIFE_SIMPLEMATER_H

#include "IMater.h"

//One Point Mater
template< std::size_t N >
class Mater: public IMater<N> {
public:
  explicit Mater(float pr): probability(pr){};
  ~Mater() =default;
  std::vector<Genome<N>*>  Mate(Genome<N>*, Genome<N>*) override;
private:
  float probability;
};

template <std::size_t N>
std::vector<Genome<N>*> Mater<N>::Mate(Genome<N> *, Genome<N> *) {
  return std::vector<Genome<N>*>(2);
}
#endif // TABLEOFLIFE_SIMPLEMATER_H
