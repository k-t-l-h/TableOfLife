#ifndef TABLEOFLIFE_ISIMULATOR_H
#define TABLEOFLIFE_ISIMULATOR_H
#include "../Genome/Genome.h"

template< std::size_t N >
class ISimulator {
public:
  virtual bool Exit(Genome<N>*) =0;
  virtual void Simulate(Genome<N>*) =0;
};
#endif // TABLEOFLIFE_ISIMULATOR_H
