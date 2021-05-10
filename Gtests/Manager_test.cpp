#include <gtest/gtest.h>
#include "../Manager/Manager.h"
#include <thread>

class GABuilder{
public:

};

struct Request{
    int id;
    std::string type;

};

// обработать задачу из очереди, определить ее тип(стратегию)
// black box strategy
TEST(TEST_WORK, non_empty_queue){
    auto tque = std::shared_ptr<std::queue<Request*>>(new std::queue <Request*>);
    auto rque = std::shared_ptr<std::queue<Result*>>(new std::queue <Result*>);

    Request request = {1, "A"};
    tque->push(&request);

    GABuilder simpleBuilder;
    Manager manager(tque,rque);
    manager.SetBuilder();

    manager.WorkCycle();

    //ASSERT_EQ(*rque->front(),1);
}


// не задаем билдер, проверяем поведение билдера по умолчанию
TEST(TEST_SET_BUILDER, default_builder){
}
