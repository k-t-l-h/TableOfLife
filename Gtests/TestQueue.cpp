#include <gtest/gtest.h>
#include "Queue.h"

TEST(TEST_QUEUE, is_empty) {
    Queue<int> queue;
    bool isEmpty = queue.Empty();
    ASSERT_EQ(isEmpty, true);
}

TEST(TEST_QUEUE, is_not_empty) {
    Queue<std::vector <int>> queue;
    std::vector <int> mass;
    mass.push_back(4);
    queue.Push(&mass);
    bool isEmpty = queue.Empty();
    ASSERT_EQ(isEmpty, true);
}

TEST(TEST_QUEUE, pop) {
    Queue<std::vector <int>> queue;
    std::vector <int> mass;
    mass.push_back(4);
    mass.push_back(89);
    queue.Push(&mass);
    std::vector<std::vector<int>> newmass = queue.Pop();
    ASSERT_EQ(newmass.size(), 1);
    bool isEmpty = queue.Empty();
    ASSERT_EQ(isEmpty, false);
}