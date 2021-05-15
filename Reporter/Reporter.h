#ifndef TABLEOFLIFE_REPORTER_H
#define TABLEOFLIFE_REPORTER_H

#include <memory>

#include "../Queue/Queue.h"

class GABuilder;
class IDatabase;
class ParserGAtoHuman;

struct Result;

class Reporter {
public:

    Reporter(std::shared_ptr<Queue<Result>> &results, std::shared_ptr<IDatabase> &);
    ~Reporter();

    void WorkCycle();

    //void work(std::unique_ptr<Result> res);

    void activate(){
        active = !active;
    }

private:

    bool active = true;

    Reporter(const Reporter & a) = delete;
    Reporter& operator=(const Reporter & a) = delete;

    std::shared_ptr<Queue<Result>> rque;
    std::shared_ptr<IDatabase> db;
};


#endif //TABLEOFLIFE_REPORTER_H