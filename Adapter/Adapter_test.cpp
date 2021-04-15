#include <gtest/gtest.h>
#include "Adapter.h"

// данный id должен присутствовать
TEST(TEST_RESULT, correct_id){
    ASSERT_EQ(1,1);
}

// результатов по данному id пока нет
TEST(TEST_RESULT, incorrect_id){
    ASSERT_EQ(1,1);
}

// переда id < 1
TEST(TEST_RESULT, id_is_null){
    ASSERT_EQ(1,1);
}

// база данных отвалилась, надо как-то обработать
TEST(TEST_DB_LIVE, db_do_not_answer){
    ASSERT_EQ(1,1);
}

