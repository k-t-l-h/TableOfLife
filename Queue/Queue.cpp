#include "Queue.h"

template<typename T>
T Queue<T>::Pop() {
    std::lock_guard<std::mutex> guard(state);
    if(container.empty()) {
        T nullReq;
        return nullReq;
    }
    T end = container.front();
    container.erase(container.begin());
    return end;
}

template<typename T>
void Queue<T>::Push(T requestResult) {
    std::lock_guard<std::mutex> guard(state);
    container.push_back(requestResult);
}

template<typename T>
bool Queue<T>::Empty() {
    std::lock_guard<std::mutex> guard(state);
    return container.empty();
}

template<typename T>
int Queue<T>::Size() { // ф созданная для тестов в основном
    return container.size();
}