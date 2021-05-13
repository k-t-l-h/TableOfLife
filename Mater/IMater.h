#ifndef TABLEOFLIFE_IMATER_H
#define TABLEOFLIFE_IMATER_H

#include "../Genome/Genome.h"

template <std::size_t N>
class IMater {
public:
    virtual std::vector<Genome<N>*> Mate(Genome<N>*, Genome<N>*) = 0;
};
#endif  // TABLEOFLIFE_IMATER_H
