#ifndef TABLEOFLIFE_BUILDER_H
#define TABLEOFLIFE_BUILDER_H
#include "../Creater/ICreator.h"
#include "../GenAlgo/GA.h"
#include "../Mater/IMater.h"
#include "../Mutator/IMutator.h"
#include "../Selector/ISelector.h"
#include "../Simulator/ISimulator.h"

template< std::size_t N >
class Builder {
public:
  explicit Builder():GA(nullptr){};
  ~Builder()= default;

  void Reset(); //создание нового ГА
  void SetMutator(); //как происходят  мутации
  void SetMater(); //как происходит отбор
  void SetSelection(); //как происходит селекция
  void SetSimulator(); //как происходит симуляция
  void SetCreator(); //как создаются поколения
  GenAlgo<N>* GetResult(); //получение ГА
private:
  GenAlgo<N>* GA;
};

template <std::size_t N> void Builder<N>::Reset() {}
template <std::size_t N> void Builder<N>::SetMutator() {}
template <std::size_t N> void Builder<N>::SetMater() {}
template <std::size_t N> void Builder<N>::SetSelection() {}
template <std::size_t N> void Builder<N>::SetSimulator() {}
template <std::size_t N> void Builder<N>::SetCreator() {}
template <std::size_t N> GenAlgo<N> *Builder<N>::GetResult() { return nullptr; }

#endif // TABLEOFLIFE_BUILDER_H
