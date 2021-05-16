#ifndef TABLEOFLIFE_IDATABASE_H
#define TABLEOFLIFE_IDATABASE_H
#include <vector>

#include "../Result/Result.h"

class IDatabase {
public:

    virtual ~IDatabase() {}

    virtual std::vector<size_t> Select(int id) = 0;
    virtual bool Insert(int id, const std::vector<size_t>&) = 0;
    virtual bool Insert(Result a) = 0;
};




#endif //TABLEOFLIFE_IDATABASE_H
