#include <gtest/gtest.h>
#include "../ParserToGA/ParserToGA.cpp"
#include "../Queue/Queue.h"
#include <string>


TEST(TEST_PARSERTOGA, work_parse_all) {
    ParserToGA<Request> parse;
    std::string request = "{\"id\": 0,\"classes\":[{\"id_groups\": 1,\"name\": \"WEB\",\"teacher\": \"Dinar\",\"count_students\": 21},{\"id_groups\":"
                          " 2,\"name\": \"C++\",\"teacher\":\"Uliana\",\"count_students\": 21},{\"id_groups\": 1,\"name\": \"ALGORITHM\",\"teacher\": "
                          "\"Krimov\",\"count_students\": 21}],\"classesNumber\": 0,\"students\": [ [1, 0, 1],[1, 0, 1],[1, 0, 1],[1, 0, 1]],\"iterations\": 5,"
                          "\"params\": {\"crossover\": \"default\",\"mutation\": \"default\",\"selector\": \"default\",\"creator\": \"default\"}}";
    ASSERT_NE(nullptr, parse.WorkCycle(&request));
    ASSERT_EQ(parse.SetStatus(), true);
}

// сломается если ключ не валидный
TEST(TEST_PARSERTOGA, validation_key) {
    ParserToGA<Request> parse;
    std::string request = "{\"idwev\": 0,\"classes\":[{\"id_groups\": 1,\"name\": \"WEB\",\"teacher\": \"Dinar\",\"count_students\": 21},{\"id_groups\":"
                          " 2,\"name\": \"C++\",\"teacher\":\"Uliana\",\"count_students\": 21},{\"id_groups\": 1,\"name\": \"ALGORITHM\",\"teacher\": "
                          "\"Krimov\",\"count_students\": 21}],\"classesNumber\": 0,\"students\": [ [1, 0, 1],[1, 0, 1],[1, 0, 1],[1, 0, 1]],\"iterations\": 5,"
                          "\"params\": {\"crossover\": \"default\",\"mutation\": \"default\",\"selector\": \"default\",\"creator\": \"default\"}}";
    ASSERT_EQ(nullptr, parse.WorkCycle(&request));
    ASSERT_EQ(parse.SetStatus(), false);
}

// проверка на отриц числа в id
TEST(TEST_PARSERTOGA, validation_negative_num) {
    ParserToGA<Request> parse;
    std::string request = "{\"id\": -1321,\"classes\":[{\"id_groups\": 1,\"name\": \"WEB\",\"teacher\": \"Dinar\",\"count_students\": 21},{\"id_groups\":"
                          " 2,\"name\": \"C++\",\"teacher\":\"Uliana\",\"count_students\": 21},{\"id_groups\": 1,\"name\": \"ALGORITHM\",\"teacher\": "
                          "\"Krimov\",\"count_students\": 21}],\"classesNumber\": 0,\"students\": [ [1, 0, 1],[1, 0, 1],[1, 0, 1],[1, 0, 1]],\"iterations\": 5,"
                          "\"params\": {\"crossover\": \"default\",\"mutation\": \"default\",\"selector\": \"default\",\"creator\": \"default\"}}";
    ASSERT_EQ(nullptr, parse.WorkCycle(&request));
    ASSERT_EQ(parse.SetStatus(), false);
}

// соблюдаем правило: количество занятий и параметры учеников, сколько занятий столько и размер каждого массива в students
TEST(TEST_PARSERTOGA, validation_students) {
    ParserToGA<Request> parse;
    std::string request = "{\"id\": 34,\"classes\":[{\"id_groups\": 1,\"name\": \"WEB\",\"teacher\": \"Dinar\",\"count_students\": 21},{\"id_groups\":"
                          " 2,\"name\": \"C++\",\"teacher\":\"Uliana\",\"count_students\": 21},{\"id_groups\": 1,\"name\": \"ALGORITHM\",\"teacher\": "
                          "\"Krimov\",\"count_students\": 21}],\"classesNumber\": 0,\"students\": [ [1, 0, 1],[1, 1],[1, 0, 1],[1, 0, 1]],\"iterations\": 5,"
                          "\"params\": {\"crossover\": \"default\",\"mutation\": \"default\",\"selector\": \"default\",\"creator\": \"default\"}}";
    ASSERT_EQ(nullptr, parse.WorkCycle(&request));
    ASSERT_EQ(parse.SetStatus(), false);
}

// не валидный json
TEST(TEST_PARSERTOGA, validation_json) {
    ParserToGA<Request> parse;
    std::string request = R"("id": 34,"classes":[{"id_groups})";
    ASSERT_EQ(nullptr, parse.WorkCycle(&request));
    ASSERT_EQ(parse.SetStatus(), false);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}