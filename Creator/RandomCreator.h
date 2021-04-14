#ifndef TABLEOFLIFE_RANDOMCREATOR_H
#define TABLEOFLIFE_RANDOMCREATOR_H

#include "ICreator.h"
#include "../Genome/Genome.h"

//Рандомно создает гены
template< std::size_t N >
class RandomCreator: public ICreator<N>{
public:
  RandomCreator() =default;
  ~RandomCreator() = default;
  std::vector<Genome<N>*> Create(size_t, size_t) override;
};

template< std::size_t N >
std::vector<Genome<N>*> RandomCreator<N>::Create(size_t size, size_t vars){
  return std::vector<Genome<N>*>(size);
};

#endif // TABLEOFLIFE_RANDOMCREATOR_H
