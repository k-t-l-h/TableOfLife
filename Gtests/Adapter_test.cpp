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
    test_db->Insert(res);
    Adapter adapt(test_db);
    EXPECT_EQ(res.result.data(),adapt.GetResult(u1).result.data());
}


// результатов по данному id пока нет
TEST(TEST_RESULT, incorrect_id){
    u::uuid u1 = boost::uuids::random_generator()();
    u::uuid u2 = boost::uuids::random_generator()();

    Result res = {u1, std::vector<size_t>()};
    auto test_db = std::make_shared<TestDatabase>();
    test_db->Insert(res);

    Adapter adapt(test_db);

    EXPECT_NE(res.id,adapt.GetResult(u2).id);
}

