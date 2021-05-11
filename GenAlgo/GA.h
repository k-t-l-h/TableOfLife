#ifndef TABLEOFLIFE_GA_H
#define TABLEOFLIFE_GA_H

#include <mutex>
#include <vector>

#include "../Creator/ICreator.h"
#include "../Genome/Genome.h"
#include "../Mater/IMater.h"
#include "../Mutator/IMutator.h"
#include "../Selector/ISelector.h"
#include "../Simulator/ISimulator.h"

template <std::size_t N>
class GenAlgo {
public:
    //TODO: добавить количество людей
    GenAlgo(size_t pt, size_t vars, size_t max)
            : populationSize(pt), variants(vars), maxIterations(max),
          Creator(nullptr),
          Selector(nullptr),
          Mater(nullptr),
          Mutator(nullptr),
          Simulator(nullptr),
          people(0),
          maxThreads(0){};

    GenAlgo(size_t pt, size_t vars, size_t max, int threads)
            : populationSize(pt), variants(vars), maxIterations(max),
              Creator(nullptr),
              Selector(nullptr),
              Mater(nullptr),
              Mutator(nullptr),
              Simulator(nullptr),
              people(0),
              maxThreads(threads){};
    ~GenAlgo() = default;
    void Run();
    std::vector<size_t> GetBest();

    ICreator<N>* Creator;
    ISelector<N>* Selector;
    IMater<N>* Mater;
    IMutator<N>* Mutator;
    ISimulator<N>* Simulator;

private:
    void RunParallel(std::vector<Genome<N>*>*, size_t start, size_t end);
    std::vector<Genome<N>*> population;
    std::size_t populationSize;
    std::size_t variants;
    std::size_t people; //количество людей
    std::size_t maxIterations;
    std::mutex Safety;
    Genome<N>* best;

    int maxThreads;
};

template <std::size_t N>
std::vector<std::size_t> GenAlgo<N>::GetBest() {
    if (best == nullptr) {
        return std::vector<size_t>(people);
    }

    std::vector<std::size_t> result;

    for (int i = 0; i < people; ++i) {
        result.push_back(best->GetGene(i));
    }
    return result;
}
template <std::size_t N>
void GenAlgo<N>::Run() {
    //создается начальная популяция
    population = Creator->Create(populationSize, people, variants);
    best = population[0];

    //начальная популяция оценивается
    for (int i = 0; i < population.size(); ++i) {
        Simulator->Simulate(population[i]);
        if (Simulator->Exit(population[i])) {
        }
        Safety.lock();
        Genome<N>* value = population[i];
        if (value->GetFitness() > best->GetFitness()) {
            best = population.at(i);
        }
        Safety.unlock();
    }

    //запускаем эволюцию
    bool status = true;
    size_t iteration = 0;
    while (status && iteration++ < maxIterations) {
        std::vector<Genome<N>*> new_population;
        //скрещиваем всех особей, по две штуки за раз
        for (int i = 0; i < populationSize; i++) {
            Genome<N>* left = Selector->Select(population);
            Genome<N>* right = Selector->Select(population);
            auto child = Mater->Mate(left, right);
            Genome<N>* lmutant = Mutator->Mutate(left);
            Genome<N>* rmutant = Mutator->Mutate(right);
            new_population.push_back(child[0]);
            new_population.push_back(child[1]);
            new_population.push_back(lmutant);
            new_population.push_back(rmutant);
        }

        //теперь переоцениваем всех
        for (int i = 0; i < new_population.size(); ++i) {
            //оцениваем каждую особь
            Simulator->Simulate(new_population[i]);
            if (Simulator->Exit(new_population[i])) {
                //не выходим сразу, т.к. может быть решение получше
                status = false;
            }
            Safety.lock();
            Genome<N>* value = new_population[i];
            if (value->GetFitness() > best->GetFitness()) {
                best = new_population[i];
            }
            Safety.unlock();
        }

        if (status) {
            //не забываем сохранить лучшую копию
            population.clear();
            population.push_back(best);
            for (int i = 0; i < populationSize - 1; ++i) {
                population.push_back(Selector->Select(new_population));
            }
        }
    }
}

template <std::size_t N>
void GenAlgo<N>::RunParallel(std::vector<Genome<N>*>*, size_t start,
                             size_t end) {}

#endif  // TABLEOFLIFE_GA_H
