#ifndef TABLEOFLIFE_REPORTER_H
#define TABLEOFLIFE_REPORTER_H

#include <memory>

class GABuilder;
class Database;
class ParserGAtoHuman;
class Queue;
struct Solution;

class Reporter {
public:

    Reporter();
    ~Reporter();

    void SetUp(std::shared_ptr<Queue<Result*>> &results, std::unique_ptr<Database> db);
    void WorkCycle();

private:
    Reporter(const Reporter & a) = delete;
    Reporter& operator=(const Reporter & a) = delete;

    std::shared_ptr<Queue<Result*>> rque;
    std::shared_ptr<Database> db;
    std::unique_ptr<ParserGAtoHuman> parser;
};


#endif //TABLEOFLIFE_REPORTER_H
