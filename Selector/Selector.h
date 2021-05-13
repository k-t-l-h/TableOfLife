#ifndef TABLEOFLIFE_SELECTOR_H
#define TABLEOFLIFE_SELECTOR_H

#include "ISelector.h"

template <std::size_t N>
class Selector final: public ISelector<N> {
public:
    explicit Selector() = default;
    ~Selector() = default;
    Genome<N>* Select(std::vector<Genome<N>*>) override;
};

template <std::size_t N>
Genome<N>* Selector<N>::Select(std::vector<Genome<N>*> genomes) {
    std::size_t value = rand() % genomes.size();
    return genomes.at(value);
}

#endif  // TABLEOFLIFE_SELECTOR_H
