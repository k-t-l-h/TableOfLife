#ifndef TABLEOFLIFE_GENOME_H
#define TABLEOFLIFE_GENOME_H

#include <bitset>
#include <shared_mutex>
#include <vector>

template <std::size_t N>
class Genome {
public:
    Genome() : size(0), fitness(0){};
    Genome(std::size_t max) : size(max), fitness(0) {
        genes = std::vector<std::bitset<N>>(max);
        for (int i = 0; i < max; ++i) {
            genes[i] = std::bitset<N>(0);
        }
    };
    Genome(const Genome& copy) {
        fitness = copy.fitness;
        size = copy.size;
        this->SetGenes(copy.genes);
    }
    ~Genome(){};

    void SetFitness(float fitness);  //установление
    float GetFitness();
    void SetGenes(std::vector<std::bitset<N>>);
    void SetGene(size_t, size_t);
    std::vector<std::bitset<N>> GetGenes();
    size_t GetGene(size_t);

private:
    // N это число-количество вариантов занятий
    std::vector<std::bitset<N>> genes;
    float fitness;
    std::size_t size;
    std::shared_timed_mutex Safety;
};

template <std::size_t N>
void Genome<N>::SetFitness(float ft) {
    //только один поток может владеть этим мьютексом
    std::unique_lock<std::shared_timed_mutex> lock(Safety, std::defer_lock);
    lock.lock(); //должен вызываться тут
    if (0 <= ft && ft <= 1) {
        fitness = ft;
    } else if (ft < 0) {
        fitness = 0;
    } else {
        fitness = 1;
    }
}

template <std::size_t N>
float Genome<N>::GetFitness() {
    //читать может много потоков
    std::shared_lock<std::shared_timed_mutex> lock(Safety, std::defer_lock);
    lock.lock();
    return fitness;
}

template <std::size_t N>
void Genome<N>::SetGenes(std::vector<std::bitset<N>> g) {
    //всё то же самое
    std::unique_lock<std::shared_timed_mutex> lock(Safety, std::defer_lock);
    lock.lock();
    genes = g;
}

template <std::size_t N>
std::vector<std::bitset<N>> Genome<N>::GetGenes() {
    std::shared_lock<std::shared_timed_mutex> lock(Safety, std::defer_lock);
    lock.lock();
    return genes;
}

template <std::size_t N>
void Genome<N>::SetGene(std::size_t index, std::size_t value) {
    //эта функция нужна для мутаций
    std::unique_lock<std::shared_timed_mutex> lock(Safety, std::defer_lock);
    lock.lock();
    genes[index] = std::bitset<N>(value);
}

template <std::size_t N>
std::size_t Genome<N>::GetGene(std::size_t index) {
    std::shared_lock<std::shared_timed_mutex> lock(Safety, std::defer_lock);
    lock.lock();
    std::bitset<N> gene = genes[index];
    auto value = gene.to_ulong();
    //возможно, есть более красивое решение?
    return static_cast<std::size_t>(value);
}

#endif  // TABLEOFLIFE_GENOME_H
