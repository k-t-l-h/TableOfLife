#ifndef TABLEOFLIFE_SIMPLEMUTATOR_H
#define TABLEOFLIFE_SIMPLEMUTATOR_H
#include "IMutator.h"

template <std::size_t N>
class SimpleMutator final : public IMutator<N> {
public:
    explicit SimpleMutator(float probability, std::size_t variants)
            : probability(probability), variants(variants){};
    ~SimpleMutator() = default;
    Genome<N>* Mutate(Genome<N>*) override;

private:
    float probability;
    std::size_t variants;
};

template <std::size_t N>
Genome<N>* SimpleMutator<N>::Mutate(Genome<N>* genome) {
    if (genome == nullptr) {
        return nullptr;
    }

    std::size_t value = genome->GetGenes().size();
    Genome<N>* mutant = new Genome<N>(*genome);

    auto check = rand();
    float rands = float(check) / (float)RAND_MAX;
    if (rands < probability) {
        size_t position = rand() % value;
        auto v = mutant->GetGene(position);
        v = v xor check;
        mutant->SetGene(position, v % variants);
    }

    return mutant;
}
#endif  // TABLEOFLIFE_SIMPLEMUTATOR_H
