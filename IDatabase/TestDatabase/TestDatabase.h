#ifndef TABLEOFLIFE_TESTDATABASE_H
#define TABLEOFLIFE_TESTDATABASE_H

#include <vector>
#include "../IDatabase.h"
#include "../../Result/Result.h"


class TestDatabase final : public IDatabase {
public:
    TestDatabase(){};

   // TestDatabase(std::vector<int> &connect) {};

    const std::vector<int>& Select(int id) override {};
    void Insert(int id, const std::vector<int>&) override {};

};


#endif //TABLEOFLIFE_TESTDATABASE_H
