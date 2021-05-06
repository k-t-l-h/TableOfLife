#ifndef TABLEOFLIFE_ISELECTOR_H
#define TABLEOFLIFE_ISELECTOR_H

#include <vector>
#include "../Genome/Genome.h"

//селектор это некоторый класс, который выбирает двух особей
//для последующего скрещивания
template <std::size_t N>
class ISelector {
public:
    virtual Genome<N>* Select(std::vector<Genome<N>*>) = 0;
};
#endif  // TABLEOFLIFE_ISELECTOR_H
