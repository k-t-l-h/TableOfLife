#include <gtest/gtest.h>
#include <vector>
#include "../Queue/Queue.cpp"
#include "../Request/Request.h"
#include "../ParserToGA/ParserToGA.h"

class TestQueue : public ::testing::Test {
public:
    Request request;
    Request request1;
    void SetUp() override {
        ParserToGA<Request> parse;
        std::string str = "{\"id\": 34,\"classes\":[{\"id_groups\": 1,\"name\": \"WEB\",\"teacher\": \"Dinar\",\"count_students\": 21},{\"id_groups\":"
                              " 2,\"name\": \"C++\",\"teacher\":\"Uliana\",\"count_students\": 21},{\"id_groups\": 1,\"name\": \"ALGORITHM\",\"teacher\": "
                              "\"Krimov\",\"count_students\": 21}],\"classesNumber\": 0,\"students\": [ [1, 0, 1],[1, 0, 1],[1, 0, 1],[1, 0, 1]],\"iterations\": 5,"
                              "\"params\": {\"crossover\": \"default\",\"mutation\": \"default\",\"selector\": \"default\",\"creator\": \"default\"}}";
        request = *parse.WorkCycle(&str);
        ParserToGA<Request> parse1;
        str = "{\"id\": 12,\"classes\":[{\"id_groups\": 67,\"name\": \"WEB_HI\",\"teacher\": \"Dinar\",\"count_students\": 21},{\"id_groups\":"
              " 2,\"name\": \"C++\",\"teacher\":\"Uliana\",\"count_students\": 21},{\"id_groups\": 1,\"name\": \"ALGORITHM\",\"teacher\": "
              "\"Krimov\",\"count_students\": 21}],\"classesNumber\": 0,\"students\": [ [0, 1, 0],[0, 1, 0],[0, 1, 0],[0, 1, 0]],\"iterations\": 5,"
              "\"params\": {\"crossover\": \"default\",\"mutation\": \"default\",\"selector\": \"default\",\"creator\": \"default\"}}";
        request1 = *parse1.WorkCycle(&str);
    }
};

// работающий Empty
TEST_F(TestQueue, is_empty) {
    Queue<int> queue;
    bool isEmpty = queue.Empty();
    ASSERT_EQ(isEmpty, true);
}

// когда кладем в очередь -> не пуста
TEST_F(TestQueue, is_not_empty) {
    Queue<Request> queue;
    queue.Push(request);
    bool isEmpty = queue.Empty();
    ASSERT_EQ(isEmpty, false);
}

// Проверка размера очереди, что-то добавляем проверяем размер, удаляем снова проверяем
TEST_F(TestQueue, sive_pop) {
    Queue<Request> queue;
    queue.Push(request);
    queue.Push(request1);

    ASSERT_EQ(queue.Size(), 2);
    queue.Pop();
    ASSERT_EQ(queue.Size(), 1);
    bool isEmpty = queue.Empty();
    ASSERT_EQ(isEmpty, false);
    queue.Pop();
    isEmpty = queue.Empty();
    ASSERT_EQ(isEmpty, true);
}

// не пожем вытащить элемент если очередь пуста, возвращается Request с зануленнымы полями
TEST_F(TestQueue, pop) {
    Queue<Request> queue;
    queue.Push(request);
    ASSERT_EQ(queue.Size(), 1);
    queue.Pop();
    ASSERT_EQ(queue.Size(), 0);
    ASSERT_EQ(queue.Empty(), true);
    auto newReq = queue.Pop();
    // все пустые
    ASSERT_EQ(newReq.id, 0);
    ASSERT_EQ(newReq.classes.size(), 0);
    ASSERT_EQ(newReq.Iterations, 0);
    ASSERT_EQ(newReq.students.size(), 0);
    ASSERT_EQ(newReq.params.creator, "");
    ASSERT_EQ(newReq.params.crossover, "");
    ASSERT_EQ(newReq.params.mutation, "");
    ASSERT_EQ(newReq.params.selector, "");
    ASSERT_EQ(queue.Empty(), true);
}

// проверка на FIFO
TEST_F(TestQueue, lilo) {
    Queue<Request> queue;
    queue.Push(request);
    ASSERT_EQ(queue.Size(), 1);
    queue.Push(request1);
    ASSERT_EQ(queue.Size(), 2);
    auto req_in_que = queue.Pop();
    ASSERT_EQ(req_in_que.id, 34);
    req_in_que = queue.Pop();
    ASSERT_EQ(req_in_que.id, 12); // последний вошел и последний вышел
}
//
//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}