#ifndef TABLEOFLIFE_GA_H
#define TABLEOFLIFE_GA_H

#include "../Genome/Genome.h"
#include <vector>
#include "../Selector/ISelector.h"
#include "../Simulator/ISimulator.h"
#include "../Mutator/IMutator.h"
#include "../Mater/IMater.h"

template< std::size_t N >
class GenAlgo {
public:
  explicit GenAlgo();
  ~GenAlgo() =default;
  void Run();
  std::vector<Genome<N>> GetBest();
private:
  void RunParallel(std::vector<Genome<N>*>*, size_t start, size_t end);
  std::vector<Genome<N>*> population;
  size_t populationSize;
  float totalFitness;

  Genome<N>** best;
  ISelector<N>* Selector;
  IMater<N>* Mater;
  IMutator<N>* Mutator;
  ISimulator<N>* Simulator;

};

template <std::size_t N>
GenAlgo<N>::GenAlgo() {}

template <std::size_t N> std::vector<Genome<N>> GenAlgo<N>::GetBest() {
  return std::vector<Genome<N>>();
}
template <std::size_t N>
void GenAlgo<N>::Run() {}

template <std::size_t N>
void GenAlgo<N>::RunParallel(std::vector<Genome<N> *> *, size_t start,
                             size_t end) {}

#endif // TABLEOFLIFE_GA_H
