#include <mutex>
#include <vector>

#ifndef TABLEOFLIFE_QUEUE_H
#define TABLEOFLIFE_QUEUE_H

template <typename T>
class Queue {
public:
    Queue() : container(0) {};
    Queue(const Queue&) = delete;

    T Pop() {
        std::lock_guard<std::mutex> guard(state);
        if (container.empty()) {
            T nullReq;
            return nullReq;
        }
        T end = container.front();
        container.erase(container.begin());
        return end;
    };

    void Push(T requestResult) {
        std::lock_guard<std::mutex> guard(state);
        container.push_back(requestResult);
    };

    bool Empty() {
        std::lock_guard<std::mutex> guard(state);
        return container.empty();
    };
    int Size() { // ф созданная для тестов в основном
        return container.size();
    };

    ~Queue() = default;

private:
    std::vector <T> container;
    std::mutex state;
};

#endif //TABLEOFLIFE_QUEUE_H
