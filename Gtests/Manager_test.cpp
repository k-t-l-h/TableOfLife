#include <gtest/gtest.h>
#include <thread>
#include <chrono>

#include "../Manager/Manager.h"
#include "../Result/Result.h"
#include "../Request/Request.h"
#include "../Queue/Queue.h"

// обработать задачу из очереди, определить ее тип(стратегию)
// black box strategy
TEST(TEST_WORK, filled_queue){
    auto tque = std::make_shared<Queue<Request>>();
    auto rque = std::make_shared<Queue<Result>>();

    Request request;
    request.id = 10;
    tque->Push(request);

    Manager manager(tque,rque);

    std::thread t(&Manager::WorkCycle, &manager);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    manager.activate();
    t.join();


    ASSERT_EQ(rque->Pop().id,10);
}

