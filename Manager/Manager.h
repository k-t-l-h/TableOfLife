#ifndef TABLEOFLIFE_MANAGER_H
#define TABLEOFLIFE_MANAGER_H

#include <memory>
#include <vector>
#include <queue>


class GABuilder;
struct Result;
struct Request;

template<class T> class Queue;

class Manager {
public:

    Manager(std::shared_ptr<std::queue<Request*>> &tasq, std::shared_ptr<std::queue<Result*>> &resq);
    ~Manager() = default;

    void SetBuilder(std::unique_ptr<GABuilder> &builder);
    void WorkCycle();

private:
    Manager& operator=(Manager &a) = delete;
    Manager() = delete;
    Manager(Manager &a) = delete;

    const Result* work(std::string, std::string, std::string, std::string);

    std::unique_ptr<GABuilder> builder;
    std::shared_ptr<std::queue<Request*>> &tque;                            //t - task
    std::shared_ptr<std::queue<Result*>> &rque;                            //r - result
};


#endif //TABLEOFLIFE_MANAGER_H
