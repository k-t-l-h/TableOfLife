#include <gtest/gtest.h>
#include "../Manager/Manager.h"




class GABuilder{

};
struct Request{
    int id;
    std::string type;
};

// обработать задачу из очереди, определить ее тип(стратегию)
TEST(TEST_WORK, non_empty_queue){
    ASSERT_EQ(1,1);
    auto tque = std::shared_ptr<std::queue<Request*>>(new std::queue <Request*>);
    auto rque = std::shared_ptr<std::queue<Result*>>(new std::queue <Result*>);

    Request request = {1, "A"};
    tque->push(&request);

    GABuilder simpleBuilder;
    Manager manager(tque,rque);

    //manager.SetBuilder(simpleBuilder);
    //manager.WorkCycle(1);

    //EXPECT_EQ(request.id, rque->pop().id);

}


// не задаем билдер, проверяем поведение билдера по умолчанию
TEST(TEST_SET_BUILDER, default_builder){
    ASSERT_EQ(1,1);
}
