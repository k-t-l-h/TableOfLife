#ifndef TABLEOFLIFE_TOPSELECTOR_H
#define TABLEOFLIFE_TOPSELECTOR_H

#include "ISelector.h"

//рулетка
template <std::size_t N>
class TopSelector final: public ISelector<N> {
public:
    explicit TopSelector() = default;
    Genome<N>* Select(std::vector<Genome<N>*>) override;
};

template <std::size_t N>
Genome<N>* TopSelector<N>::Select(std::vector<Genome<N>*> genomes){
    if (genomes.empty()) {
        return nullptr;
    }
    double total = 0;
    for (int i = 0; i < genomes.size(); ++i) {
        //по идее  мы не должны получить нулевого зверя
        //но всё же
        if (genomes.at(i) != nullptr) {
            auto gene = genomes.at(i);
            total += gene->GetFitness();
        }
    }

    if (total == 0) {
        int rands = rand() % genomes.size();
        return genomes.at(rands);
    }

    double max = static_cast<double>(rand() % int(total));
    for (int i = 0; i < genomes.size(); ++i) {
        if (genomes.at(i) == nullptr) {
            continue;
        }
        auto gene = genomes.at(i);
        max -= gene->GetFitness();
        if (max < 0) {
            return genomes.at(i);
        }
    }

    //рано или поздно мы выберем особь
    //но это план б
    return genomes.at(0);
}

#endif  // TABLEOFLIFE_TOPSELECTOR_H
