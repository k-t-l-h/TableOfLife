#ifndef TABLEOFLIFE_TESTDATABASE_H
#define TABLEOFLIFE_TESTDATABASE_H
#include <vector>
#include "../IDatabase.h"
#include "../../Result/Result.h"
class Result;

class TestDatabase: public IDatabase {
public:
    TestDatabase();
    TestDatabase(sql *connect);
    ~TestDatabase();

    int ** Select(int id);
    void Insert(int id, int **);

private:
    std::vector<Result*> connection;
};


#endif //TABLEOFLIFE_TESTDATABASE_H
