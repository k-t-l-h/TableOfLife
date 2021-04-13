#include <mutex>
#include <vector>

#ifndef TABLEOFLIFE_QUEUE_H
#define TABLEOFLIFE_QUEUE_H

template <typename T>
class Queue {
public:
    Queue() : container(nullptr), size(0), realSize(0) {};
    Queue(const Queue&) = delete;
    ~Queue() {
        delete[] container;
    }

    std::vector <T> Pop();

    void Push(T * Queue);

    bool Empty();

private:
    std::vector <T> * container;
    int size;
    int realSize;
    std::mutex state;

    void resize();
};

#endif //TABLEOFLIFE_QUEUE_H
