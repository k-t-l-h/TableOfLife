#ifndef TABLEOFLIFE_RANDOMCREATOR_H
#define TABLEOFLIFE_RANDOMCREATOR_H

#include "../Genome/Genome.h"
#include "ICreator.h"
#include <cmath>
#include <thread>

//Рандомно создает гены
template <std::size_t N>
class RandomCreator final: public ICreator<N> {
public:
    RandomCreator() { srand(time(0)); };
    ~RandomCreator() = default;
    std::vector<Genome<N> *> Create(std::size_t all, std::size_t length,
                                    std::size_t vars) override;

private:
    static void GenerateInThread(std::vector<Genome<N>*> *generation,
                          std::size_t num, std::size_t vars, std::size_t length);
};


template <std::size_t N>
void RandomCreator<N>::GenerateInThread(std::vector<Genome<N>*> *generation,
                                        std::size_t num, std::size_t vars, std::size_t length){

    for (size_t i = 0; i < num; ++i) {
        auto genome = new Genome<N>(length);

        for (std::size_t j = 0; j < length; ++j) {
            auto value = static_cast<std::size_t>(rand() % vars);
            genome->SetGene(j, value);
        }
        generation->push_back(genome);
    }
};

template <std::size_t N>
std::vector<Genome<N> *> RandomCreator<N>::Create(std::size_t all,
                                                  std::size_t length,
                                                  std::size_t vars) {

    //создаем вектор геномов
    auto *generation = new std::vector<Genome<N> *>();
    //выделяем ему фиксированное количество элементов
    generation->reserve(all);

    //смотрим сколько можем создать тредов
    auto nthreads = std::thread::hardware_concurrency();

    //увеличиваем число до максимума
    auto  parts = static_cast<std::size_t>(ceil(double(all) / nthreads));
    //если число тредов больше числа частей
    nthreads = parts == 0 ? all : nthreads;
    //этот же случай
    parts = parts > 0 ? parts: 1;
    std::vector<std::thread> threads;


    for (int i = 0; i < nthreads; ++i) {
        parts = parts > all ? all: parts;
        all -= parts;
        std::thread t(GenerateInThread, std::ref(generation),
                      parts,vars, length);
        threads.push_back(std::move(t));
    }


    for (std::thread & th : threads)
    {
        if (th.joinable())
            th.join();
    }

    return *generation;
}

#endif  // TABLEOFLIFE_RANDOMCREATOR_H
