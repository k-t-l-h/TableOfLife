#include <gtest/gtest.h>
#include "../ParserToGA/ParserToGA.h"
#include "../Queue/Queue.h"


TEST(TEST_PARSERTOGA, test_set_status) {
    Queue<Request> q{};
    ParserToGA<Request> parse(q);
    parse.SetStatus();
    ASSERT_EQ((bool)parse.workStatus, true);
}

TEST(TEST_PARSERTOGA, test_work_validation_all) {
    Queue<Request> queue;
    ParserToGA parse(queue);
    std::string str = "{\"id\": 34, \"field\": 0, \"iterations\": \"12:30\", \"strategy\" : \"sriiiing\", "
                      "\"data\" : { \"profession\": \"mechanic\", \"profession\": \"mechanic\"}}";
    parse.WorkCycle(&str);

    ASSERT_EQ(queue.Empty(), false);
}

TEST(TEST_PARSERTOGA, test_work_validation_data) {
    Queue<Request> queue;
    ParserToGA<Request> parse(queue);
    std::string str = "{\"id\": 34, \"field\": 0, \"iterations\": \"12:30\", \"strategy\" : \"sriiiing\", "
                        "\"data\" : { ion\": \"mechanic\", \"profession\": \"mechanic\"}}";
    parse.WorkCycle(&str);
    ASSERT_EQ(queue.Empty(), true);
}

TEST(TEST_PARSERTOGA, test_work_validation_field) {
    Queue<Request> queue;
    ParserToGA<Request> parse(queue);
    std::string str = "{\"id\": 34, \"field\": text, \"iterations\": \"12:30\", \"strategy\" : \"sriiiing\", "
                      "\"data\" : { \"profession\": \"mechanic\", \"profession\": \"mechanic\"}}";
    parse.WorkCycle(&str);
    ASSERT_EQ(queue.Empty(), true);
}

TEST(TEST_PARSERTOGA, test_work_validation_iterations) {
    Queue<Request> queue;
    ParserToGA<Request> parse(queue);
    std::string str = "{\"id\": 34, \"field\": 0, \"iterations\": \"ceewwwef0\", \"strategy\" : \"sriiiing\", "
                      "\"data\" : { \"profession\": \"mechanic\", \"profession\": \"mechanic\"}}";
    parse.WorkCycle(&str);
    ASSERT_EQ(queue.Empty(), true);
}

TEST(TEST_PARSERTOGA, test_work_validation_strategy) {
    Queue<Request> queue;
    ParserToGA<Request> parse(queue);
    std::string str = "{\"id\": 34, \"field\": 0, \"iterations\": \"12:30\", \"strategy\" : \"\", "
                      "\"data\" : { \"profession\": \"mechanic\", \"profession\": \"mechanic\"}}";
    parse.WorkCycle(&str);
    ASSERT_EQ(queue.Empty(), true);
}
