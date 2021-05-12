#include <memory>
#include <gtest/gtest.h>
#include "../Adapter/Adapter.h"
#include "../Result/Result.h"
#include "../IDatabase/TestDatabase/TestDatabase.h"
#include <vector>


// данный id должен присутствовать
TEST(TEST_RESULT, correct_id){
    Result res = {3, std::vector<int>()};
    auto test_db = std::make_shared<TestDatabase>();
    test_db->Insert(res.id, res.result);
    Adapter adapt(test_db);
    EXPECT_EQ(0,adapt.GetResult(3).size());
}


// результатов по данному id пока нет
TEST(TEST_RESULT, incorrect_id){
Result res = {3, std::vector<int>()};
auto test_db = std::make_shared<TestDatabase>();
test_db->Insert(res.id, res.result);

Adapter adapt(test_db);

EXPECT_EQ(0,adapt.GetResult(8).size());
}



// переда id < 1
TEST(TEST_RESULT, id_is_null){
Result res = {3, std::vector<int>()};
auto test_db = std::shared_ptr<IDatabase>(new TestDatabase);
test_db->Insert(res.id, res.result);

Adapter adapt(test_db);

EXPECT_EQ(0,adapt.GetResult(0).size());
}


// возварщаем тот же вектор который полжили
TEST(TEST_RESULT, vector_check){

// фиктивные данные
std::vector<int> my_vec = {1,0,1};
Result res = {3, my_vec};

// mock-db
auto test_db = std::shared_ptr<IDatabase>(new TestDatabase);
test_db->Insert(res.id, res.result);

// наш адаптер
Adapter adapt(test_db);

EXPECT_EQ(true,(my_vec == adapt.GetResult(3)));
}


/*
// база данных отвалилась, надо как-то обработать
TEST(TEST_DB_LIVE, db_do_not_answer){
    ASSERT_EQ(1,1);
}
*/