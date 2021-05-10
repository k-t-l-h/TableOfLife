#ifndef TABLEOFLIFE_BUILDER_H
#define TABLEOFLIFE_BUILDER_H

#include "../Creator/ICreator.h"
#include "../Creator/SimpleCreator.h"
#include "../Creator/RandomCreator.h"

#include "../GenAlgo/GA.h"

#include "../Mater/IMater.h"
#include "../Mater/SimpleMater.h"
#include "../Mater/TwoDotsMater.h"

#include "../Mutator/IMutator.h"
#include "../Mutator/ReverseMutator.h"
#include "../Mutator/SimpleMutator.h"

#include "../Selector/ISelector.h"
#include "../Selector/Selector.h"
#include "../Selector/TopSelector.h"

#include "../Simulator/ISimulator.h"
#include "../Simulator/Simulator.h"

template <std::size_t N>
class Builder {
public:
    explicit Builder() : variants(0){
       auto tmp = new GenAlgo<N>(1, 1, 1);
       GA = tmp;
    };

    ~Builder() {
            delete GA;
    };
    void Reset(std::size_t);  //создание нового ГА

    void SetMutator(float);         //как происходят  мутации
    void SetReverseMutator(float);  //чтобы оправдать выбор

    //как происходит отбор
    void SetMater(float);

    void Set2PointsMater(float);

    void SetSelection();  //как происходит селекция
    void SetTopSelection();

    void SetSimulator();  //как происходит симуляция

    void SetCreator();  //как создаются поколения
    void SetRandomCreator();

    GenAlgo<N>* GetResult();  //получение ГА
private:
    GenAlgo<N>* GA;
    std::size_t variants;
};

//при ресете необходимо указывать новое количество вариантов
template <std::size_t N>
void Builder<N>::Reset(std::size_t variants) {
    //подсчет начальной популяции идет в зависимости от вариантов
    //т.к. необходимо убедиться, что достаточно вариантов,
    //чтобы каждый ген встретился хотя бы один раз

    // TODO: просчитать вероятность
    std::size_t population = variants*2;

    GenAlgo<N>* tmp = new GenAlgo<N>(population, variants, 10);
    delete GA;
    GA = tmp;
}

template <std::size_t N>
void Builder<N>::SetMutator(float probability) {
    SimpleMutator<N>* sm = new SimpleMutator<N>(probability, variants);
    delete GA->Mutator;
    GA->Mutator = sm;
}

template <std::size_t N>
void Builder<N>::SetReverseMutator(float probability) {
    ReverseMutator<N>* sm = new ReverseMutator<N>(probability, variants);
    delete GA->Mutator;
    GA->Mutator = sm;
}

template <std::size_t N>
void Builder<N>::SetMater(float probability) {
    Mater<N>* mate = new Mater<N>(probability);
    delete GA->Mater;
    GA->Mater = mate;
}

template <std::size_t N>
void Builder<N>::Set2PointsMater(float probability) {
    TwoPointsMater<N>* mate = new TwoPointsMater<N>(probability);
    delete GA->Mater;
    GA->Mater = mate;
}

template <std::size_t N>
void Builder<N>::SetSelection() {
    Selector<N>* sl = new Selector<N>();
    delete GA->Selector;
    GA->Selector = sl;
}

template <std::size_t N>
void Builder<N>::SetTopSelection() {
    TopSelector<N>* sl = new TopSelector<N>();
    delete GA->Selector;
    GA->Selector = sl;
}

template <std::size_t N>
void Builder<N>::SetSimulator() {
    Simulator<N>* sm = new Simulator<N>();
    delete GA->Simulator;
    GA->Simulator = sm;
}

template <std::size_t N>
void Builder<N>::SetCreator() {
    SimpleCreator<N>* cr = new SimpleCreator<N>();
    delete GA->Creator;
    GA->Creator = cr;
}

template <std::size_t N>
void Builder<N>::SetRandomCreator() {
    RandomCreator<N>* cr = new RandomCreator<N>();
    delete GA->Creator;
    GA->Creator = cr;
}

template <std::size_t N>
GenAlgo<N>* Builder<N>::GetResult() {
    return GA;
}

#endif  // TABLEOFLIFE_BUILDER_H
