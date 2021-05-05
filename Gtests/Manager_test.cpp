#include <gtest/gtest.h>
#include "../Manager/Manager.h"




class GABuilder;
class Request;
template<class T> class Queue;

// обработать задачу из очереди, определить ее тип(стратегию)
TEST(TEST_WORK, non_empty_queue){
    ASSERT_EQ(1,1);
    auto tque = std::shared_ptr<Queue<Request*>>(new Queue <Request*>);
    auto rque = std::shared_ptr<Queue<Result*>>(new Queue <Result*>);

    Request request;
    request.id = 3;
    tque->put(&request);

    GABuilder simpleBuilder;
    Manager manager;

    manager.Setup(tque,rque);
    manager.SetBuilder(simpleBuilder);
    manager.WorkCycle(1);

    EXPECT_EQ(request.id, rque->pop().id);

}


// не задаем билдер, проверяем поведение билдера по умолчанию
TEST(TEST_SET_BUILDER, default_builder){
    ASSERT_EQ(1,1);
}
