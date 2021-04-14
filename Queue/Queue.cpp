#include "Queue.h"

template <typename T>
std::vector<T> Queue<T>::Pop() {
    return std::vector<T>();
}

template <typename T>
void Queue<T>::Push(T * Queue) {
    *Queue = *Queue;
}

template <typename T>
bool Queue<T>::Empty() {
    return false;
}