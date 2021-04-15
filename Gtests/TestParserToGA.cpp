#include <gtest/gtest.h>
#include "../ParserToGA/ParserToGA.h"
#include "../Queue/Queue.h"


TEST(TEST_PARSERTOGA, test_set_status) {
    ParserToGA parse;
    parse.SetStatus();
    ASSERT_EQ((bool)parse.workStatus, true);
}

TEST(TEST_PARSERTOGA, test_work_validation_all) {
    ParserToGA parse;
    std::string str = "{\"id\": 34, \"field\": 0, \"iterations\": \"12:30\", \"strategy\" : \"sriiiing\", "
                      "\"data\" : { \"profession\": \"mechanic\", \"profession\": \"mechanic\"}}";
    parse.WorkCycle(&str);
    Queue<Request> queue;
    ASSERT_EQ(queue.Empty(), false);
}

TEST(TEST_PARSERTOGA, test_work_validation_data) {
    ParserToGA parse;
    std::string str = "{\"id\": 34, \"field\": 0, \"iterations\": \"12:30\", \"strategy\" : \"sriiiing\", "
                        "\"data\" : { ion\": \"mechanic\", \"profession\": \"mechanic\"}}";
    parse.WorkCycle(&str);
    Queue<Request> queue;
    ASSERT_EQ(queue.Empty(), true);
}

TEST(TEST_PARSERTOGA, test_work_validation_field) {
    ParserToGA parse;
    std::string str = "{\"id\": 34, \"field\": text, \"iterations\": \"12:30\", \"strategy\" : \"sriiiing\", "
                      "\"data\" : { \"profession\": \"mechanic\", \"profession\": \"mechanic\"}}";
    parse.WorkCycle(&str);
    Queue<Request> queue;
    ASSERT_EQ(queue.Empty(), true);
}

TEST(TEST_PARSERTOGA, test_work_validation_iterations) {
    ParserToGA parse;
    std::string str = "{\"id\": 34, \"field\": 0, \"iterations\": \"ceewwwef0\", \"strategy\" : \"sriiiing\", "
                      "\"data\" : { \"profession\": \"mechanic\", \"profession\": \"mechanic\"}}";
    parse.WorkCycle(&str);
    Queue<Request> queue;
    ASSERT_EQ(queue.Empty(), true);
}

TEST(TEST_PARSERTOGA, test_work_validation_strategy) {
    ParserToGA parse;
    std::string str = "{\"id\": 34, \"field\": 0, \"iterations\": \"12:30\", \"strategy\" : \"\", "
                      "\"data\" : { \"profession\": \"mechanic\", \"profession\": \"mechanic\"}}";
    parse.WorkCycle(&str);
    Queue<Request> queue;
    ASSERT_EQ(queue.Empty(), true);
}
