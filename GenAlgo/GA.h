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
              maxThreads(0){};

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
              maxThreads(threads){};

    ~GenAlgo() {
        FreePopulation(population);
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

    for (int i = 0; i < people; ++i) {
        result.push_back(best->GetGene(i));
    }
    return result;
}
template <std::size_t N>
void GenAlgo<N>::Run() {
    //создается начальная популяция
    if (Creator == nullptr || Simulator == nullptr) {
        return;
    }

    population = Creator->Create(populationSize, people, variants);
    best = population[0];

    //сколько тредов мы можем создать
    auto nthreads =
            maxThreads == 0 ? std::thread::hardware_concurrency() : maxThreads;
    nthreads = nthreads > std::thread::hardware_concurrency()
               ? std::thread::hardware_concurrency()
               : nthreads;
    //сколько частей в начальной популяции
    auto parts =
            static_cast<std::size_t>(ceil(double(populationSize) / nthreads));
    //если число тредов больше числа частей
    nthreads = parts == 0 ? populationSize : nthreads;
    //этот же случай
    parts = parts > 0 ? parts : 1;
    std::vector<std::thread> threads;

    //начальная популяция оценивается
    for (int i = 0; i < nthreads;) {
        size_t end = (++i) * parts;
        end = end > populationSize ? populationSize : end;
        std::thread t(&GenAlgo<N>::FitnessParallel, this, std::ref(population),
                      i * parts, end);
        threads.push_back(std::move(t));
    }

    for (std::thread& th : threads) {
        if (th.joinable()) th.join();
    }
    //очищаем и переиспользуем
    threads.clear();

    //запускаем эволюцию
    size_t iteration = 0;
    while (!Simulator->Exit(best) && iteration++ < maxIterations) {
        std::vector<Genome<N>*> new_population;
        //скрещиваем всех особей

        parts = static_cast<std::size_t>(ceil(double(populationSize) / nthreads));
        for (int i = 0; i < nthreads; i++) {
            int count = i * parts > populationSize ? populationSize : i * parts;
            std::thread t(&GenAlgo<N>::CrossoverParallel, this,
                          std::ref(new_population), count);
            threads.push_back(std::move(t));
        }

        for (std::thread& th : threads) {
            if (th.joinable()) th.join();
        }

        threads.clear();
        parts = static_cast<std::size_t>(ceil(double(populationSize) / nthreads));
        for (int i = 0; i < nthreads; i++) {
            int count = i * parts > populationSize ? populationSize : i * parts;
            std::thread t(&GenAlgo<N>::MutateParallel, this, std::ref(new_population),
                          count);
            threads.push_back(std::move(t));
        }

        for (std::thread& th : threads) {
            if (th.joinable()) th.join();
        }
        threads.clear();

        //теперь переоцениваем всех
        parts = static_cast<std::size_t>(
                ceil(double(new_population.size()) / nthreads));
        parts = parts > 0 ? parts : 1;
        for (int i = 0; i < maxThreads;) {
            size_t end = (++i) * parts;
            end = end > new_population.size() ? new_population.size() : end;
            std::thread t(&GenAlgo<N>::FitnessParallel, this,
                          std::ref(new_population), i * parts, end);
            threads.push_back(std::move(t));
        }

        for (std::thread& th : threads) {
            if (th.joinable()) th.join();
        }
        threads.clear();

        if (!Simulator->Exit(best)) {
            //не забываем сохранить лучшую копию
            population.push_back(std::move(best));
            //освобождаем старое поколение
            FreePopulation(population);
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

        for (auto& ch : child) {
            pp.push_back(ch);
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
        delete g;
    }
}

#endif  // TABLEOFLIFE_GA_H
