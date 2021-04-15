#include <gtest/gtest.h>
#include "Manager.h"

// обработать задачу из очереди, определить ее тип(стратегию) и запустить нужную последовательность действий
TEST(TEST_WORK, non_empty_queue){
    ASSERT_EQ(1,1);
}

// очередь пуста - спим
TEST(TEST_WORK_CYCLE, empty_q){
    ASSERT_EQ(1,1);
}

// очередь пуста, значит в очереди решений в результате работы цикла должно появиться решение
TEST(TEST_WORK_CYCLE, non_empty_q){
    ASSERT_EQ(1,1);
}

// не задаем билдер, проверяем поведение билдера по умолчанию
TEST(TEST_SET_BUILDER, default_builder){
    ASSERT_EQ(1,1);
}

// задаем определенный билдер, проверяем поведение
TEST(TEST_SET_BUILDER, defined_builder){
    ASSERT_EQ(1,1);
}