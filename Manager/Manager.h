#ifndef TABLEOFLIFE_MANAGER_H
#define TABLEOFLIFE_MANAGER_H

#include <memory>


class GABuilder;
class Queue;

class Manager {
public:
    Manager() = default;
    ~Manager() = default;

    void Setup(std::shared_ptr<Queue> &tasq, std::shared_ptr<Queue> &resq);
    void WorkCycle();

private:

    Manager& operator=() = delete;
    Manager(Manager &a) = delete;

    void setBuilder(std::unique_ptr<builder> &builder);

    std::unique_ptr<GABuilder> builder;
    std::shared_ptr<Queue> tque;                            //t - task
    std::shared_ptr<Queue> rque;                            //r - result
};


#endif //TABLEOFLIFE_MANAGER_H
