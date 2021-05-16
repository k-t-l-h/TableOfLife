#ifndef TABLEOFLIFE_MANAGER_H
#define TABLEOFLIFE_MANAGER_H

#include <memory>
#include <vector>
#include <queue>
#include "../GABuilder/Builder.h"
#include "../Request/Request.h"
#include "../Queue/Queue.h"

struct Result;
struct Request;


class Manager {
public:

    Manager(std::shared_ptr<Queue<Request>> &tasq, std::shared_ptr<Queue<Result>> &resq);
    ~Manager() = default;

    void WorkCycle();

    void activate(){
        active = !active;
    }

private:
    Manager& operator=(Manager &a) = delete;
    Manager() = delete;
    Manager(Manager &a) = delete;

    void work( Request task);

    bool active = true;

    std::shared_ptr<Queue<Request>> tque;                            //t - task
    std::shared_ptr<Queue<Result>> rque;                             //r - result
};


#endif //TABLEOFLIFE_MANAGER_H