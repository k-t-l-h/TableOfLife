#ifndef TABLEOFLIFE_GENOME_H
#define TABLEOFLIFE_GENOME_H

#include <vector>
#include <bitset>

template< std::size_t N >
class Genome {
public:
  Genome():size(0), fitness(0){};
  Genome(std::size_t max):size(max), fitness(0){
  genes = std::vector<std::bitset<N>>(max);
    for (int i = 0; i < max; ++i) {
      genes[i] = std::bitset<N>(0);
    }
  };
  ~Genome(){};

  void SetFitness(float fitness); //установление
  float GetFitness();
  void SetGenes(std::vector< std::bitset<N>>);
  void SetGene(size_t, size_t);
  std::vector< std::bitset<N>> GetGenes();
  size_t GetGene(size_t);
private:
  //N это число-количество вариантов занятий
  std::vector< std::bitset<N>> genes;
  float fitness;
  std::size_t size;
};

template <std::size_t N> void Genome<N>::SetFitness(float fitness) {}

template <std::size_t N> float Genome<N>::GetFitness() { return 0; }

template <std::size_t N> void Genome<N>::SetGenes(std::vector<std::bitset<N>>) {
}

template <std::size_t N> std::vector<std::bitset<N>> Genome<N>::GetGenes() {
  return genes;
}
template <std::size_t N> void Genome<N>::SetGene(size_t, size_t) {}
template <std::size_t N> size_t Genome<N>::GetGene(size_t) { return 0; }

#endif // TABLEOFLIFE_GENOME_H
