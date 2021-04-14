#include <mutex>
#include <vector>

#ifndef TABLEOFLIFE_QUEUE_H
#define TABLEOFLIFE_QUEUE_H

template <typename T>
class Queue {
public:
    int size;

    Queue() : container(nullptr), size(0) {};
    Queue(const Queue&) = delete;

    std::vector <T> Pop();

    void Push(T * Queue);

    bool Empty();

    ~Queue() {
        delete[] container;
    }

private:
    std::vector <T> * container;
    std::mutex state;
};

#endif //TABLEOFLIFE_QUEUE_H
