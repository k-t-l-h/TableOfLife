#include <gtest/gtest.h>
#include "Server.h"
#include <iostream>

TEST(TEST_SERVER, set_up) {
    Server server;
    int start = server.SetUp();
    ASSERT_EQ(start, 0);
}

TEST(TEST_SERVER, shut_down) {
    Server server;
    int off = server.ShutDown();
    ASSERT_EQ(off, 0);
}

TEST(TEST_SERVER, run) {
    Server server;
    int run = server.Run();
    ASSERT_EQ(run, 0);
}

TEST(TEST_SERVER, response_reporter) {
    Server server;
    ASSERT_EQ(server.responseReporter(40), 0);
}

TEST(TEST_SERVER, send_answer) {
    Server server;
    std::string str = "edwdewdwdewd"
    int status = server.SendAnswer(str);
    ASSERT_EQ(status, 0);
}

TEST(TEST_SERVER, send_json) {
    Server server;
    int status = server.SendJson(40);
    ASSERT_EQ(status, 0);
}