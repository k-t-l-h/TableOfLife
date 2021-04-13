#ifndef TABLEOFLIFE_ICREATOR_H
#define TABLEOFLIFE_ICREATOR_H
#include "../Genome/Genome.h"

template< std::size_t N >
class ICreator{
public:
  virtual std::vector<Genome<N>*> Create(size_t, size_t) =0;
};

#endif // TABLEOFLIFE_ICREATOR_H
