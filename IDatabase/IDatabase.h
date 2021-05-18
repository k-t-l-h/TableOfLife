#ifndef TABLEOFLIFE_IDATABASE_H
#define TABLEOFLIFE_IDATABASE_H
#include <vector>

#include "../Result/Result.h"
#include <boost/uuid/uuid.hpp>

class IDatabase {
public:

    virtual ~IDatabase() {}

    virtual std::vector<size_t> Select(u::uuid) = 0;
    virtual bool Insert(u::uuid id, const std::vector<size_t>&) = 0;
    virtual bool Insert(Result a) = 0;
};




#endif //TABLEOFLIFE_IDATABASE_H
