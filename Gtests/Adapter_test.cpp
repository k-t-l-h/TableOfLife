#include <gtest/gtest.h>
#include <memory>

#include "../Adapter/Adapter.h"
#include "../Result/Result.h"
#include "../IDatabase/TestDatabase/TestDatabase.h"
#include <vector>

// данный id должен присутствовать
TEST(TEST_RESULT, correct_id){

    std::vector<int> test_res;
    Result res = {3, test_res};
    std::shared_ptr<TestDatabase> pt;
    pt = std::make_shared<TestDatabase>();
    std::shared_ptr<IDatabase> test_db = std::static_pointer_cast<IDatabase>(pt);
    test_db->Insert(res.id, res.result);

    Adapter adapt(std::ref(test_db));

    EXPECT_EQ(nullptr,adapt.GetResult(3));
}

// результатов по данному id пока нет
TEST(TEST_RESULT, incorrect_id){
    std::vector<int> test_res;
    Result res = {3, test_res};
    auto test_db = std::shared_ptr<IDatabase>();
    test_db->Insert(res.id, res.result);

    Adapter adapt(test_db);

    EXPECT_EQ(nullptr,adapt.GetResult(8));
}

// переда id < 1
TEST(TEST_RESULT, id_is_null){
    std::vector<int> test_res;
    Result res = {3, test_res};
    auto test_db = std::shared_ptr<IDatabase>();
    test_db->Insert(res.id, res.result);

    Adapter adapt(test_db);

    EXPECT_EQ(nullptr,adapt.GetResult(0));
}

// база данных отвалилась, надо как-то обработать
TEST(TEST_DB_LIVE, db_do_not_answer){
}


