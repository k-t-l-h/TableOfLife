#include <gtest/gtest.h>
#include <memory>

#include "Adapter.h"
#include "../Result/Result.h"
#include "../IDatabase/TestDatabase/TestDatabase.h"


// данный id должен присутствовать
TEST(TEST_RESULT, correct_id){

    Result res = {3, nullptr};
    auto test_db = std::shared_ptr<IDatabase>(new TestDatabase);
    test_db->Insert(res.id, res.result);

    Adapter adapt(test_db);

    EXPECT_EQ(nullptr,adapt.GetResult(3));
}

// результатов по данному id пока нет
TEST(TEST_RESULT, incorrect_id){
    Result res = {3, nullptr};
    auto test_db = std::shared_ptr<IDatabase>(new TestDatabase);
    test_db->Insert(res.id, res.result);

    Adapter adapt(test_db);

    EXPECT_EQ(nullptr,adapt.GetResult(8));
}

// переда id < 1
TEST(TEST_RESULT, id_is_null){
    Result res = {3, nullptr};
    auto test_db = std::shared_ptr<IDatabase>(new TestDatabase);
    test_db->Insert(res.id, res.result);

    Adapter adapt(test_db);

    EXPECT_EQ(nullptr,adapt.GetResult(0));
}

// база данных отвалилась, надо как-то обработать
TEST(TEST_DB_LIVE, db_do_not_answer){
    ASSERT_EQ(1,1);
}

