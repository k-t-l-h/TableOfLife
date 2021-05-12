#include <gtest/gtest.h>
#include "../Server/Server.cpp"
#include "../ParserToGA/ParserToGA.h"
#include <iostream>

TEST(TEST_SERVER, take_body_send_parser) {
    Server server;
    server.SetUp();
    server.PackReqParser();
    server = server;
//    ASSERT_EQ(start, 0);
}

//
//TEST(TEST_SERVER, test_shut_down) {
//    Server server;
//    int off = server.ShutDown();
//    ASSERT_EQ(off, 0);
//}
//
//TEST(TEST_SERVER, test_run) {
//    Server server;
//    int run = server.Run();
//    ASSERT_EQ(run, 0);
//}
//
//TEST(TEST_SERVER, response_reporter) {
//    Server server;
//    server.SetUp();
//    server.responseReporter(40);
//    ASSERT_EQ(0, 0);
//    server.ShutDown();
//}
//
//TEST(TEST_SERVER, test_send_answer) {
//    Server server;
//    int status = server.SendAnswer();
//    ASSERT_EQ(status, 0);
//}
//
//TEST(TEST_SERVER, test_send_json) {
//    Server server;
//    int status = server.SendJson(40);
//    ASSERT_EQ(status, 0);
//}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}