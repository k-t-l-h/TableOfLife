#include <gtest/gtest.h>
#include <thread>

#include "../Manager/Manager.h"
#include "../Result/Result.h"
#include "../Request/Request.h"
#include "../Queue/Queue.h"


// обработать задачу из очереди, определить ее тип(стратегию)
// black box strategy
TEST(TEST_WORK, non_empty_queue){
    auto tque = std::make_shared<Queue<Request>>();
    auto rque = std::make_shared<Queue<Result>>();

    Request request;
    tque->Push(request);

    //GABuilder simpleBuilder;
    Manager manager(tque,rque);
    //manager.SetBuilder();

    manager.WorkCycle();

    ASSERT_EQ(rque->Pop().id,0);
}

/*
// не задаем билдер, проверяем поведение билдера по умолчанию
TEST(TEST_SET_BUILDER, default_builder){
    ASSERT_EQ(1,1);
}
*/