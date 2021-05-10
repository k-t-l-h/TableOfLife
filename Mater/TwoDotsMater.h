#ifndef TABLEOFLIFE_TWODOTSMATER_H
#define TABLEOFLIFE_TWODOTSMATER_H

#include "IMater.h"

template <std::size_t N>
class TwoPointsMater : public IMater<N> {
public:
    explicit TwoPointsMater(float pr) : probability(pr){ srand(time(0)); };
    ~TwoPointsMater() = default;
    std::vector<Genome<N>*> Mate(Genome<N>*, Genome<N>*) override;

private:
    float probability;
};

template <std::size_t N>
std::vector<Genome<N>*> TwoPointsMater<N>::Mate(Genome<N>* left,
                                                Genome<N>* right) {
    //говорят в бусте есть хорошие генераторы чисел :)))
    //узнаем в следующих сериях

    std::vector<Genome<N>*> children;
    if (left == nullptr || right == nullptr) {
        //что-то пошло не так, но нас это уже не должно беспокоить
        return children;
    }

    auto value = rand();
    float rands = float(value) / (float)RAND_MAX;

    //вообще-то эти длины должны быть одинаковыми
    //но мы не исключаем этих проблем
    std::vector<std::bitset<N>> lg = left->GetGenes();
    std::size_t lefts = lg.size();

    std::vector<std::bitset<N>> rg = right->GetGenes();
    std::size_t rights = rg.size();

    //точки кроссовера могут находиться только в общем диапазоне
    std::size_t general = lefts < rights ? lefts : rights;

    std::size_t fisrtp = rand() % general;
    std::size_t secondp = rand() % general;

    if (fisrtp < secondp) {
        std::swap(fisrtp, secondp);
    }

    Genome<N>* lchild = new Genome<N>(lefts);
    Genome<N>* rchild = new Genome<N>(rights);

    if (rands < probability) {
        for (std::size_t i = 0; i < general; ++i) {
            lchild->SetGene(i, left->GetGene(i));
            rchild->SetGene(i, right->GetGene(i));
        }
    } else {
        for (std::size_t i = 0; i < fisrtp; ++i) {
            lchild->SetGene(i, left->GetGene(i));
            rchild->SetGene(i, right->GetGene(i));
        }

        for (std::size_t i = fisrtp; i < secondp; ++i) {
            lchild->SetGene(i, right->GetGene(i));
            rchild->SetGene(i, left->GetGene(i));
        }

        for (std::size_t i = secondp; i < general; ++i) {
            lchild->SetGene(i, left->GetGene(i));
            rchild->SetGene(i, right->GetGene(i));
        }
    }
    //заполняем кусочки оставшиеся
    //заполняем правого ребенка
    for (std::size_t i = general; i < rights; ++i) {
        rchild->SetGene(i, right->GetGene(i));
    }

    //заполняем левого ребенка
    for (std::size_t i = general; i < lefts; ++i) {
        lchild->SetGene(i, lchild->GetGene(i));
    }

    children.push_back(rchild);
    children.push_back(lchild);

    return children;
}

#endif  // TABLEOFLIFE_TWODOTSMATER_H