#ifndef TABLEOFLIFE_TOPSELECTOR_H
#define TABLEOFLIFE_TOPSELECTOR_H

#include "ISelector.h"

//рулетка
template <std::size_t N>
class TopSelector : public ISelector<N> {
public:
    explicit TopSelector() = default;
    Genome<N>* Select(std::vector<Genome<N>*>*) override;
};

template <std::size_t N>
Genome<N>* TopSelector<N>::Select(std::vector<Genome<N>*>* genomes) {
    if (genomes == nullptr) {
        return nullptr;
    }

    double total = 0;
    for (int i = 0; i < genomes->size(); ++i) {
        //по идее  мы не должны получить нулевого зверя
        //но всё же
        if (*genomes[i] != nullptr) {
            total += *genomes[i].GetFitness();
        }
    }
    if (total == 0) {
        int rands = rand() % genomes->size();
        return genomes[rands];
    }

    double max = static_cast<double>(rand()) % total;
    for (int i = 0; i < genomes->size(); ++i) {
        if (genomes[i] == nullptr) {
            continue;
        }
        max -= genomes[i].GetFitness();
        if (max < 0) {
            return genomes[i];
        }
    }

    //рано или поздно мы выберем особь
    //но это план б
    return genomes[0];
}

#endif  // TABLEOFLIFE_TOPSELECTOR_H
