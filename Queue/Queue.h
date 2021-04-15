#include <mutex>
#include <vector>

#ifndef TABLEOFLIFE_QUEUE_H
#define TABLEOFLIFE_QUEUE_H

template<typename T>
class Queue {
public:
    int size;

    Queue() : container(nullptr), size(0) {};
    Queue(const Queue& q){
        container = q.container;
        size = q.size;
    };
    ~Queue() {
        delete[] container;
    }

    std::vector <T> Pop();

    static void Push(T * Queue);

    bool Empty();

private:
    std::vector <T> * container;
    std::mutex state;
};

#endif //TABLEOFLIFE_QUEUE_H
