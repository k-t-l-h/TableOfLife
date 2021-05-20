#ifndef TABLEOFLIFE_IMUTATOR_H
#define TABLEOFLIFE_IMUTATOR_H

#include "../Genome/Genome.h"

template< std::size_t N >
class IMutator {
public:
    virtual Genome<N>* Mutate(Genome<N>*) =0;
};
#endif // TABLEOFLIFE_IMUTATOR_H
