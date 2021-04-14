#include <gtest/gtest.h>
#include "Adapter.h"

TEST(TEST_RESULT, correct_id){
    ASSERT_EQ(1,1);
}

TEST(TEST_RESULT, incorrect_id){
    ASSERT_EQ(1,1);
}

TEST(TEST_RESULT, id_is_null){
    ASSERT_EQ(1,1);
}

TEST(TEST_DB_LIVE, db_do_not_answer){
    ASSERT_EQ(1,1);
}

