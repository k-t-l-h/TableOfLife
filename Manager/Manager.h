#ifndef TABLEOFLIFE_MANAGER_H
#define TABLEOFLIFE_MANAGER_H

#include <memory>
#include <vector>
#include <queue>


class GABuilder;
struct Result;
struct Request;
template <typename T> class Queue;

class Manager {
public:

    Manager(std::shared_ptr<Queue<Request*>> tasq, std::shared_ptr<Queue<Result*>> resq);
    ~Manager() = default;

    void SetBuilder();
    void WorkCycle();

private:
    Manager& operator=(Manager &a) = delete;
    Manager() = delete;
    Manager(Manager &a) = delete;

    void work(std::unique_ptr<Request> task);

    std::unique_ptr<GABuilder> builder;
    std::shared_ptr<Queue<Request*>> tque;                            //t - task
    std::shared_ptr<Queue<Result*>> rque;                            //r - result
};


#endif //TABLEOFLIFE_MANAGER_H