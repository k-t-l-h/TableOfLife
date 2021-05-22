#include <gtest/gtest.h>
#include "../Reporter/Reporter.h"

#include <vector>
#include <memory>

#include "../Result/Result.h"
#include "../IDatabase/TestDatabase/TestDatabase.h"
#include "../Queue/Queue.h"
#include <thread>
#include <chrono>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators



//решение извлекается из непустой очереди и кладется в базу данных, нужно проверить наличие этого решения в бд в результате обработки
TEST(TEST_WORK_CYCLE, non_empty_result_queue){

    auto rque = std::make_shared<Queue<Result>>();
    auto test_db = std::shared_ptr<IDatabase>(new TestDatabase);

    Reporter reporter(rque, test_db);

    u::uuid u1 = boost::uuids::random_generator()();
    Result result = {u1, std::vector<size_t>()};
    rque->Push(result);

    std::thread t(&Reporter::WorkCycle, &reporter);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    reporter.activate();
    t.join();

    EXPECT_EQ(result.id, test_db->Select(result.id).id);

}





