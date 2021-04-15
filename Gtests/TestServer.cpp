#include <gtest/gtest.h>
#include "../Server/Server.h"
#include "../ParserToGA/ParserToGA.h"
#include <iostream>

TEST(TEST_SERVER, test_set_up) {
    Server server;
    int start = server.SetUp();
    ASSERT_EQ(start, 0);
}

TEST(TEST_SERVER, test_shut_down) {
    Server server;
    int off = server.ShutDown();
    ASSERT_EQ(off, 0);
}

TEST(TEST_SERVER, test_run) {
    Server server;
    int run = server.Run();
    ASSERT_EQ(run, 0);
}

TEST(TEST_SERVER, response_reporter) {
    Server server;
    server.SetUp();
    server.responseReporter(40);
    ASSERT_EQ(0, 0);
    server.ShutDown();
}

TEST(TEST_SERVER, test_send_answer) {
    Server server;
    int status = server.SendAnswer();
    ASSERT_EQ(status, 0);
}

TEST(TEST_SERVER, test_send_json) {
    Server server;
    int status = server.SendJson(40);
    ASSERT_EQ(status, 0);
}