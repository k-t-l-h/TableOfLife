#ifndef TABLEOFLIFE_TESTDATABASE_H
#define TABLEOFLIFE_TESTDATABASE_H

#include <vector>
#include "../IDatabase.h"
#include "../../Result/Result.h"

class Result;


class TestDatabase: public IDatabase {
public:
    TestDatabase();
    TestDatabase(vector<int> &connect);
    ~TestDatabase() override;

    const std::vector<int>& Select(int id) override;
    void Insert(int id, const std::vector<int>&) override;

private:
    std::vector<Result*> connection;
};


#endif //TABLEOFLIFE_TESTDATABASE_H
