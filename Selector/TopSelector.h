#ifndef TABLEOFLIFE_TOPSELECTOR_H
#define TABLEOFLIFE_TOPSELECTOR_H

template< std::size_t N >
class TopSelector: public ISelector<N> {
public:
  explicit TopSelector() = default;;
  Genome<N>* Select(std::vector<Genome<N>*>*) override;
};

template <std::size_t N>
Genome<N>* TopSelector<N>::Select(std::vector<Genome<N> *>*) {
return nullptr;


#endif // TABLEOFLIFE_TOPSELECTOR_H
