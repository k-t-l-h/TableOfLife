#ifndef TABLEOFLIFE_TESTDATABASE_H
#define TABLEOFLIFE_TESTDATABASE_H

#include <vector>
#include "../IDatabase.h"
#include "../../Result/Result.h"

class TestDatabase: public IDatabase {
public:
    TestDatabase() = default;
    ~TestDatabase() override;

    std::vector<int> Select(int id) override;
    bool Insert(int id, const std::vector<int>&) override;

private:
    std::vector<int> data = std::vector<int>();
    int id = 0;
};


#endif //TABLEOFLIFE_TESTDATABASE_H