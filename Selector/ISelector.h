#ifndef TABLEOFLIFE_ISELECTOR_H
#define TABLEOFLIFE_ISELECTOR_H

#include <vector>
#include "../Genome/Genome.h"


template< std::size_t N >
class ISelector{
  virtual Genome<N>* Select(std::vector<Genome<N>*>*) =0;
};
#endif // TABLEOFLIFE_ISELECTOR_H
