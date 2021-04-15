#ifndef TABLEOFLIFE_MANAGER_H
#define TABLEOFLIFE_MANAGER_H

#include <memory>


class GABuilder;
class Queue;
class Result;

class Manager {
public:
    Manager() = default;
    ~Manager() = default;

    void Setup(std::shared_ptr<Queue> &tasq, std::shared_ptr<Queue> &resq);
    void SetBuilder(std::unique_ptr<GABuilder> &builder);
    void WorkCycle();

private:

    Manager& operator=() = delete;
    Manager(Manager &a) = delete;

    const Result* work(const char* strategy);

    std::unique_ptr<GABuilder> builder;
    std::shared_ptr<Queue> tque;                            //t - task
    std::shared_ptr<Queue> rque;                            //r - result
};


#endif //TABLEOFLIFE_MANAGER_H
