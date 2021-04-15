#include <gtest/gtest.h>
#include "Reporter.h"

#include <vector>

TEST(TEST_WORK_CYCLE, empty_result_queue){
    ASSERT_EQ(1,1);
}

//решение извлекается из непустой очереди и кладется в базу данных, нужно проверить наличие этого решения в бд в результате обработки
TEST(TEST_WORK_CYCLE, non_empty_result_queue){
    ASSERT_EQ(1,1);
}
//рассмотреть кейс если база данных не отвечает и попробовать сложить данное решение обратно, после чего попробовать еще арз подконнектиться к бд
TEST(STRESS_TEST_WORK_CYCLE, db_no_answer){
    ASSERT_EQ(1,1);
}

// проверить наличие настроек по умолчанию
TEST(TEST_SETUP, default_reporter_setup){
    ASSERT_EQ(1,1);
}
// задание определенных настроек
TEST(TEST_SETUP, defined_reporter_setup){
    ASSERT_EQ(1,1);
}