#include <gtest/gtest.h>
#include "../ParserToHuman/ParserToHuman.h"
#include <string>
#include "../Result/Result.h"
#include <iostream>

TEST(TEST_PARSE, data1){
    u::uuid u1 = boost::uuids::random_generator()();
    std::vector<size_t> vec = {0,0,1,1,1,0};
    std::vector<Classes> cls= {{"Algo","Krimov", 2},{"OS","Linus", 3}};
    Result res = {u1, vec, cls, cls.size()};
    ParserToHuman parser;

    std::cout << parser.GetReadable(res) << std::endl;
}



