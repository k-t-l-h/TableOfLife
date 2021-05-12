#include <mutex>
#include <vector>

#ifndef TABLEOFLIFE_QUEUE_H
#define TABLEOFLIFE_QUEUE_H

template <typename T>
class Queue {
public:
    Queue() : container(0) {};
    Queue(const Queue&) = delete;

    T Pop();

    void Push(T q);

    bool Empty();
    int Size();

    ~Queue() = default;

private:
    std::vector <T> container;
    std::mutex state;
};

#endif //TABLEOFLIFE_QUEUE_H
