#include <memory>
#include <gtest/gtest.h>
#include "../Adapter/Adapter.h"
#include "../Result/Result.h"
#include "../IDatabase/TestDatabase/TestDatabase.h"
#include <vector>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators

namespace u = boost::uuids;


// данный id должен присутствовать
TEST(TEST_RESULT, correct_id){
    u::uuid u1 = boost::uuids::random_generator()();
    Result res = {u1, std::vector<size_t>()};
    auto test_db = std::make_shared<TestDatabase>();
    test_db->Insert(res.id, res.result);
    Adapter adapt(test_db);
    EXPECT_EQ(res.result.data(),adapt.GetResult(u1).data());
}


// результатов по данному id пока нет
TEST(TEST_RESULT, incorrect_id){
    u::uuid u1 = boost::uuids::random_generator()();
    u::uuid u2 = boost::uuids::random_generator()();

    Result res = {u1, std::vector<size_t>()};
    auto test_db = std::make_shared<TestDatabase>();
    test_db->Insert(res.id, res.result);

    Adapter adapt(test_db);

EXPECT_NE(res.result.data(),adapt.GetResult(u2).data());
}



// возварщаем тот же вектор который полжили
TEST(TEST_RESULT, vector_check){

// фиктивные данные
std::vector<size_t> my_vec = {1,0,1};

    u::uuid u1 = boost::uuids::random_generator()();
    Result res = {u1, my_vec};
    auto test_db = std::make_shared<TestDatabase>();
    test_db->Insert(res.id, res.result);
    // наш адаптер
    Adapter adapt(test_db);
    EXPECT_EQ(true,(my_vec == adapt.GetResult(u1)));
}
