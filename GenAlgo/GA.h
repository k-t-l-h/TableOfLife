#ifndef TABLEOFLIFE_GA_H
#define TABLEOFLIFE_GA_H

#include <mutex>
#include <vector>
#include <thread>
#include <cmath>

#include "../Creator/ICreator.h"
#include "../Genome/Genome.h"
#include "../Mater/IMater.h"
#include "../Mutator/IMutator.h"
#include "../Selector/ISelector.h"
#include "../Simulator/ISimulator.h"

template <std::size_t N>
class GenAlgo {
public:
    GenAlgo(size_t pt, size_t vars, size_t max, size_t people)
            : populationSize(pt),
              variants(vars),
              maxIterations(max),
              Creator(nullptr),
              Selector(nullptr),
              Mater(nullptr),
              Mutator(nullptr),
              Simulator(nullptr),
              people(people),
              maxThreads(1){};

    GenAlgo(size_t pt, size_t vars, size_t max, size_t people, int threads)
            : populationSize(pt),
              variants(vars),
              maxIterations(max),
              Creator(nullptr),
              Selector(nullptr),
              Mater(nullptr),
              Mutator(nullptr),
              Simulator(nullptr),
              people(people),
              maxThreads(1){};

    ~GenAlgo() {
//        FreePopulation(population);
        /*
        delete Creator;
        delete Mater;
        delete Mutator;
        delete Selector;
        delete Simulator;
         */
    }

    void Run();
    std::vector<size_t> GetBest();

    ICreator<N>* Creator;
    ISelector<N>* Selector;
    IMater<N>* Mater;
    IMutator<N>* Mutator;
    ISimulator<N>* Simulator;

private:
    void FreePopulation(std::vector<Genome<N>*>);
    void FitnessParallel(std::vector<Genome<N>*>&, size_t start, size_t end);
    void CrossoverParallel(std::vector<Genome<N>*>&, size_t);
    void MutateParallel(std::vector<Genome<N>*>&, size_t);
    std::vector<Genome<N>*> population;
    std::size_t populationSize;
    std::size_t variants;
    std::size_t people;
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
    auto res = best->GetGenes();
    for (int i = 0; i <res.size(); ++i) {
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
void GenAlgo<N>::FitnessParallel(std::vector<Genome<N>*>& pp, size_t start,
                                 size_t end) {
    if (Simulator == nullptr) {
        return;
    }

    for (int i = start; i < end; ++i) {
        Simulator->Simulate(pp[i]);
        if (Simulator->Exit(pp[i])) {
        }
        Safety.lock();
        Genome<N>* value = pp[i];
        if (value != nullptr && value->GetFitness() > best->GetFitness()) {
            best = pp.at(i);
        }
        Safety.unlock();
    }
}

template <std::size_t N>
void GenAlgo<N>::CrossoverParallel(std::vector<Genome<N>*>& pp, size_t count) {
    if (Selector == nullptr || Mater == nullptr) {
        return;
    }
    //здесь логика заковыристее
    //т.к. передается массив, куда засовываются потомки
    for (int i = 0; i < count; ++i) {
        Genome<N>* left = Selector->Select(population);
        Genome<N>* right = Selector->Select(population);
        auto child = Mater->Mate(left, right);

        for (int j = 0;j < child.size(); j++) {
            pp.push_back(child[j]);
        }
    }
}

template <std::size_t N>
void GenAlgo<N>::MutateParallel(std::vector<Genome<N>*>& pp, size_t count) {
    if (Selector == nullptr || Mutator == nullptr) {
        return;
    }
    //здесь логика заковыристее
    //т.к. передается массив, куда засовываются потомки
    for (int i = 0; i < count; ++i) {
        Genome<N>* mom = Selector->Select(population);
        Genome<N>* mutant = Mutator->Mutate(mom);
        pp.push_back(mutant);
    }
}
template <std::size_t N>
void GenAlgo<N>::FreePopulation(std::vector<Genome<N>*> generation) {
    for (auto& g : generation) {
        if (g != nullptr)
{       delete g;
}  }
}

#endif  // TABLEOFLIFE_GA_H
