#include <gtest/gtest.h>
#include "../Reporter/Reporter.h"

#include <vector>
#include <memory>

#include "../Result/Result.h"
#include "../IDatabase/TestDatabase/TestDatabase.h"
#include "../Queue/Queue.h"
#include <thread>
#include <chrono>



//решение извлекается из непустой очереди и кладется в базу данных, нужно проверить наличие этого решения в бд в результате обработки
TEST(TEST_WORK_CYCLE, non_empty_result_queue){

    auto rque = std::make_shared<Queue<Result>>();
    auto test_db = std::shared_ptr<IDatabase>(new TestDatabase);

    Reporter reporter(rque, test_db);

    Result result = {3, std::vector<size_t>()};
    rque->Push(result);

    std::thread t(&Reporter::WorkCycle, &reporter);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    reporter.activate();
    t.join();

    EXPECT_EQ(result.result, test_db->Select(result.id));

}
/*

//рассмотреть кейс если база данных не отвечает и попробовать сложить данное решение обратно, после чего попробовать еще арз подконнектиться к бд
TEST(STRESS_TEST_WORK_CYCLE, db_no_answer){
    ASSERT_EQ(1,1);
    auto rque = std::shared_ptr<Queue<Result*>>(new Queue <Result*>);
    auto test_db = std::shared_ptr<IDatabase>(nullptr);

    Reporter reporter;
    reporter.SetUp(rque, test_db);


    Result result = {3, nullptr};
    rque->push(&result);

    reporter.WorkCycle( Queue.size() );

    EXPECT_EQ(rque->top.id, result.id);
}

// проверить наличие настроек по умолчанию
TEST(TEST_SETUP, default_reporter_setup){
    Reporter reporter;
    EXPECT_EQ(1,1);
}
*/




