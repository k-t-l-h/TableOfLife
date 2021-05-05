#ifndef TABLEOFLIFE_MANAGER_H
#define TABLEOFLIFE_MANAGER_H

#include <memory>


class GABuilder;
class Result;
class Request;

template<class T> class Queue;

class Manager {
public:
    Manager() = default;
    ~Manager() = default;

    void Setup(std::shared_ptr<Queue<Request*>> &tasq, std::shared_ptr<Queue<Result*>> &resq);
    void SetBuilder(std::unique_ptr<GABuilder> &builder);
    void WorkCycle();

private:

    Manager& operator=() = delete;
    Manager(Manager &a) = delete;

    const Result* work(std::string, std::string, std::string, std::string);

    std::unique_ptr<GABuilder> builder;
    std::shared_ptr<Queue<Request*>> tque;                            //t - task
    std::shared_ptr<Queue<Result*>> rque;                            //r - result
};


#endif //TABLEOFLIFE_MANAGER_H
