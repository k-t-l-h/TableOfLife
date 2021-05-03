#ifndef TABLEOFLIFE_SIMPLEMATER_H
#define TABLEOFLIFE_SIMPLEMATER_H

#include "IMater.h"

// One Point Mater
template <std::size_t N>
class Mater : public IMater<N> {
public:
    explicit Mater(float pr) : probability(pr){ srand(time(nullptr)); };
    ~Mater() = default;
    std::vector<Genome<N>*> Mate(Genome<N>*, Genome<N>*) override;

private:
    float probability;
};

template <std::size_t N>
std::vector<Genome<N>*> Mater<N>::Mate(Genome<N>* left, Genome<N>* right) {
    std::vector<Genome<N>*> children;
    if (left == nullptr || right == nullptr) {
        //что-то пошло не так, но нас это не должно беспокоить
        return children;
    }

    //вообще-то эти длины должны быть одинаковыми
    //но мы не исключаем этих проблем
    std::vector<std::bitset<N>> lg = left->GetGenes();
    std::size_t lefts = lg.size();

    std::vector<std::bitset<N>> rg = right->GetGenes();
    std::size_t rights = rg.size();

    Genome<N>* lchild = new Genome<N>(lefts);
    Genome<N>* rchild = new Genome<N>(rights);

    for (std::size_t i = 0; i < lefts && i < rights; ++i) {
        auto value = rand();
        float rand = float(value) / (float)RAND_MAX;
        if (rand < probability) {
            lchild->SetGene(i, left->GetGene(i));
            rchild->SetGene(i, left->GetGene(i));
        } else {
            lchild->SetGene(i, right->GetGene(i));
            rchild->SetGene(i, right->GetGene(i));
        }
    }

    //заполняем кусочки оставшиеся
    //заполняем правого ребенка
    for (std::size_t i = lefts; i < rights; ++i) {
        rchild->SetGene(i, right->GetGene(i));
    }

    //заполняем левого ребенка
    for (std::size_t i = rights; i < lefts; ++i) {
        lchild->SetGene(i, lchild->GetGene(i));
    }

    children.push_back(rchild);
    children.push_back(lchild);

    return children;
}
#endif  // TABLEOFLIFE_SIMPLEMATER_H
