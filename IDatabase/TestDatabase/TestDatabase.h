#ifndef TABLEOFLIFE_TESTDATABASE_H
#define TABLEOFLIFE_TESTDATABASE_H

#include <vector>
#include "../IDatabase.h"
#include "../../Result/Result.h"

class TestDatabase: public IDatabase {
public:
    TestDatabase() = default;
    ~TestDatabase() override;

    std::vector<size_t> Select(int id) override;
    bool Insert(int id, const std::vector<size_t>&) override;
    bool Insert(Result a) override;

private:
    std::vector<size_t> data = std::vector<size_t>();
    int id = 0;
};


#endif //TABLEOFLIFE_TESTDATABASE_H