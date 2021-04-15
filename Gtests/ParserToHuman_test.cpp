#include <gtest/gtest.h>
#include "../ParserToHuman/ParserToHuman.h"
#include <string>


TEST(TEST_PARSE, data1){
    int **arr = nullptr;
    ParserToHuman parser;
    ASSERT_EQ(0, strcmp(parser.GetReadable(arr),""));
}

TEST(TEST_PARSE, data2){
    ASSERT_EQ(1, 1);
}