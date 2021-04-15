#ifndef TABLEOFLIFE_GA_H
#define TABLEOFLIFE_GA_H

#include <vector>

#include "../Genome/Genome.h"
#include "../Selector/ISelector.h"
#include "../Simulator/ISimulator.h"
#include "../Mutator/IMutator.h"
#include "../Mater/IMater.h"
#include "../Creator/ICreator.h"

template< std::size_t N >
class GenAlgo {
public:
  GenAlgo()= default;;
  ~GenAlgo() =default;
  void Run();
  std::vector<int> GetBest();

  Genome<N>* best;
  ICreator<N>* Creator;
  ISelector<N>* Selector;
  IMater<N>* Mater;
  IMutator<N>* Mutator;
  ISimulator<N>* Simulator;
private:
  void RunParallel(std::vector<Genome<N>*>*, size_t start, size_t end);
  std::vector<Genome<N>*> population;
  size_t populationSize;
  float totalFitness;

};

template <std::size_t N>
std::vector<int> GenAlgo<N>::GetBest() {
  return std::vector<int>(1);
}
template <std::size_t N> void GenAlgo<N>::Run() {}

template <std::size_t N>
void GenAlgo<N>::RunParallel(std::vector<Genome<N> *> *, size_t start,
                             size_t end) {}

#endif // TABLEOFLIFE_GA_H
