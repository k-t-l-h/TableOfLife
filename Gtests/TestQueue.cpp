#include <gtest/gtest.h>
#include "vector"
#include "Queue.cpp"

TEST(TEST_QUEUE, is_empty) {
    Queue<int> queue;
    bool isEmpty = queue.Empty();
    ASSERT_EQ(isEmpty, true);
}

TEST(TEST_QUEUE, is_not_empty) {
    Queue<std::vector <int>> queue;
    std::vector <int> mass;
    mass.push_back(4);
    queue.Push(mass);
    bool isEmpty = queue.Empty();
    ASSERT_EQ(isEmpty, false);
}

TEST(TEST_QUEUE, pop) {
    Queue<std::vector <int>> queue;
    std::vector <int> mass;
    std::vector <int> NewMass;
    mass.push_back(4);
    mass.push_back(89);
    NewMass.push_back(314);
    NewMass.push_back(678);
    queue.Push(NewMass);
    queue.Push(mass);
    auto newmass = queue.Pop();
    ASSERT_EQ(newmass.size(), 2);
    ASSERT_EQ(newmass[0], 314);
    ASSERT_EQ(newmass[1], 678);
    ASSERT_EQ(queue.Size(), 1);
    bool isEmpty = queue.Empty();
    ASSERT_EQ(isEmpty, false);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}