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
};

template <std::size_t N>
std::vector<Genome<N> *> SimpleCreator<N>::Create(std::size_t all,
                                                  std::size_t length,
                                                  std::size_t vars) {
    auto *generation = new std::vector<Genome<N> *>();

    for (std::size_t i = 0; i < all; ++i) {
        auto genome = new Genome<N>(length);
        for (std::size_t j = 0; j < length; ++j) {
            auto value = static_cast<std::size_t>((i + j) % vars);
            genome->SetGene(j, value);
        }
        generation->push_back(genome);
    }
    return *generation;
}

#endif  // TABLEOFLIFE_SIMPLECREATOR_H
