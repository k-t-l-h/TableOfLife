#ifndef TABLEOFLIFE_REPORTER_H
#define TABLEOFLIFE_REPORTER_H

#include <memory>

#include "../Queue/Queue.h"
#include "../GABuilder/Builder.h"
#include "../IDatabase/IDatabase.h"
#include "../Result/Result.h"


class Reporter {
public:

    Reporter(std::shared_ptr<Queue<Result>> &, std::shared_ptr<IDatabase> &);
    ~Reporter();

    void WorkCycle();


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