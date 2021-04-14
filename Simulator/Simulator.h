#ifndef TABLEOFLIFE_SIMULATOR_H
#define TABLEOFLIFE_SIMULATOR_H


#include "ISimulator.h"

//класс симулятор просто берет один геном и считает для него новую
//функцию приспособленности по заданному правилу
//правило задается через SetRule()
//функция остановки задается через SetExit()
template< std::size_t N >
class Simulator: public ISimulator<N> {
  public:
    explicit Simulator() =default;
    bool Exit(Genome<N>*) override;
    void Simulate(Genome<N>*) override;
    void SetRule(void (*)(Genome<N>*));
    void SetExit(bool (*)(Genome<N>*));
  private:
    void (*RuleF)(Genome<N>*);
    bool (*ExitF)(Genome<N>*);
};

template< std::size_t N >
bool Simulator<N>::Exit(Genome<N>* g){
  return ExitF(g);
}
template <std::size_t N>
void Simulator<N>::Simulate(Genome<N> *g){
  RuleF(g);
}
template <std::size_t N>
void Simulator<N>::SetRule(void (*Rule)(Genome<N> *)){
  RuleF = Rule;
}
template <std::size_t N>
void Simulator<N>::SetExit(bool (*Exit)(Genome<N> *)){
    ExitF = Exit;

};



#endif // TABLEOFLIFE_SIMULATOR_H

