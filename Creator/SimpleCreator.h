#ifndef TABLEOFLIFE_SIMPLECREATOR_H
#define TABLEOFLIFE_SIMPLECREATOR_H

#include "ICreator.h"
#include "../Genome/Genome.h"

template <std::size_t N>
class SimpleCreator final : public ICreator<N> {
public:
    SimpleCreator() = default;
    ~SimpleCreator() = default;
    //первый параметр - сколько создавать, второй - сколько вариантов одного гена
    std::vector<Genome<N> *> Create(std::size_t all, std::size_t length,
                                    std::size_t vars) override;

private:
    static void GenerateInThread(std::vector<Genome<N>*> *generation,
                                 std::size_t num, std::size_t vars, std::size_t length,
                                 std::size_t offset);
};

template <std::size_t N>
std::vector<Genome<N> *> SimpleCreator<N>::Create(std::size_t all,
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
                      parts,vars, length, parts*i);
        threads.push_back(std::move(t));
    }


    for (std::thread & th : threads)
    {
        if (th.joinable())
            th.join();
    }

    return *generation;
}
template<std::size_t N>
void SimpleCreator<N>::GenerateInThread(std::vector<Genome<N> *> *generation,
                                        std::size_t num,
                                        std::size_t vars,
                                        std::size_t length, std::size_t offset) {

    for (size_t i = 0; i < num; ++i) {
        auto genome = new Genome<N>(length);

        for (std::size_t j = 0; j < length; ++j) {
            auto value = static_cast<std::size_t>((i + offset + j) % vars);
            genome->SetGene(j, value);
        }
        generation->push_back(genome);
    }
}

#endif  // TABLEOFLIFE_SIMPLECREATOR_H
