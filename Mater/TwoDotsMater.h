#ifndef TABLEOFLIFE_TWODOTSMATER_H
#define TABLEOFLIFE_TWODOTSMATER_H

#include "IMater.h"

template< std::size_t N >
class TwoPointsMater: public IMater<N> {
public:
  explicit TwoPointsMater(float pr): probability(pr){};
  ~TwoPointsMater() =default;
  std::vector<Genome<N>*>  Mate(Genome<N>*, Genome<N>*) override;
private:
  float probability;
};

template <std::size_t N>
std::vector<Genome<N>*> TwoPointsMater<N>::Mate(Genome<N> *, Genome<N> *) {
return std::vector<Genome<N>*>(2);
}

#endif // TABLEOFLIFE_TWODOTSMATER_H
