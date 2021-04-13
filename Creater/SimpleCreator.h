#ifndef TABLEOFLIFE_SIMPLECREATOR_H
#define TABLEOFLIFE_SIMPLECREATOR_H
#include "ICreator.h"
#include "../Genome/Genome.h"

template< std::size_t N >
class SimpleCreator: public ICreator<N>{
public:
  SimpleCreator() =default;
  ~SimpleCreator() = default;
  //первый параметр - сколько создавать, второй - сколько вариантов одного гена
  std::vector<Genome<N>*> Create(size_t, size_t) override;
};

template< std::size_t N >
std::vector<Genome<N>*> SimpleCreator<N>::Create(size_t size, size_t vars){
    return std::vector<Genome<N>*>(size);
};

#endif // TABLEOFLIFE_SIMPLECREATOR_H
