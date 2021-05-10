#ifndef TABLEOFLIFE_RANDOMCREATOR_H
#define TABLEOFLIFE_RANDOMCREATOR_H

#include "ICreator.h"
#include "../Genome/Genome.h"

//Рандомно создает гены
template <std::size_t N>
class RandomCreator : public ICreator<N> {
public:
    RandomCreator() { srand(time(0)); };
    ~RandomCreator() = default;
    std::vector<Genome<N> *> Create(std::size_t all, std::size_t length,
                                    std::size_t vars) override;
};

template <std::size_t N>
std::vector<Genome<N> *> RandomCreator<N>::Create(std::size_t all,
                                                  std::size_t length,
                                                  std::size_t vars) {
    auto *generation = new std::vector<Genome<N> *>();

    for (std::size_t i = 0; i < all; ++i) {
        auto genome = new Genome<N>(length);
        for (std::size_t j = 0; j < length; ++j) {
            auto value = static_cast<std::size_t>(rand() % vars);
            genome->SetGene(j, value);
        }
        generation->push_back(genome);
    }
    return *generation;
}

#endif  // TABLEOFLIFE_RANDOMCREATOR_H
