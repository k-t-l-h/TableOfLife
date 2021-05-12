#ifndef TABLEOFLIFE_REPORTER_H
#define TABLEOFLIFE_REPORTER_H

#include <memory>
#include <queue>

class GABuilder;
class IDatabase;
class ParserGAtoHuman;

struct Result;

class Reporter {
public:

    Reporter(std::shared_ptr<std::queue<Result*>> &results, std::shared_ptr<IDatabase> &);
    ~Reporter();

    //void SetUp(std::shared_ptr<std::queue<Result*>> &results, std::shared_ptr<IDatabase> &db);

    void WorkCycle(int);

    //void work(std::unique_ptr<Result> res);

private:

    Reporter(const Reporter & a) = delete;
    Reporter& operator=(const Reporter & a) = delete;

    std::shared_ptr<std::queue<Result*>> rque;
    std::shared_ptr<IDatabase> db;
};


#endif //TABLEOFLIFE_REPORTER_H