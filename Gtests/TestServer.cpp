#include <gtest/gtest.h>
#include "../Server/Server.h"
#include "../ParserToGA/ParserToGA.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio.hpp>
#include <boost/asio.hpp>
#include <boost/asio/write.hpp>
#include "../General/General.h"
#include <../Client/Client.h>
#include <iostream>
#include <thread>
#include <string>

// ошибка в UUID
TEST(TEST_SERVER, take_body_send_parser) {
    General gen = General(2);
    gen.turnOn();
    boost::asio::io_service io_service;
    Server s(io_service, 8081, &gen);
    std::thread tr([&] { io_service.run(); });

    boost::asio::io_context context;
    Client client(context, "127.0.0.1", 8081);
    client.start();

    std::string buffer("GET /status/b5fc218e-dd2hvhbjhberwhbrehbjrehjbrecfcfg HTTP/1.1\\rContent-Type: application/text\\rHost: 127.0.0.1:8081\\rContent-Length: 0\r");
    client.send(buffer);
    std::string str = client.read();
    int res = std::stoi(str.substr(9, 3));
    ASSERT_EQ(400, res);
    gen.turnOff();
    io_service.stop();
    tr.join();
}


TEST(TEST_SERVER, test_shut_down) {
    General gen = General(2);
    boost::asio::io_service io_service;
    gen.turnOn();
    Server s(io_service, 8081, &gen);
    std::thread tr([&] { io_service.run(); });

    boost::asio::io_context context;
    Client client(context, "127.0.0.1", 8081);
    client.start();

    std::string buffer("POST HTTP/1.1\rContent-Type: application/json\rHost: 127.0.0.1:8081\rContent-Length: 494\r\n\r\n "
                       "{\"classes\":[{\"id_groups\": 1,\"name\": \"WEB\",\"teacher\": \"Dinar\",\"count_students\": 21}, "
                       "{\"id_groups\": 2,\"name\": \"C++\",\"teacher\":\"Uliana\",\"count_students\": 21},{\"id_groups\": "
                       "1,\"name\": \"ALGORITHM\",\"teacher\": \"Krimov\",\"count_students\": 21}],\"classesNumber\": 0,\"students\": "
                       "[ [1, 0, 1], [1, 0, 1], [1, 0, 1], [1, 0, 1]],\"iterations\": 5, \"params\": {\"crossover\": \"default\", \"mutation\": "
                       "\"default\", \"selector\": \"default\", \"creator\": \"default\"}}");
    client.send(buffer);
    std::string str = client.read();
    int res = std::stoi(str.substr(9, 3));
    ASSERT_EQ(204, res);

    gen.turnOff();
    io_service.stop();
    tr.join();
}
// не может распарсить json
TEST(TEST_SERVER, test_run) {
    General gen = General(2);
    boost::asio::io_service io_service;
    gen.turnOn();
    Server s(io_service, 8081, &gen);
    std::thread tr([&] { io_service.run(); });

    boost::asio::io_context context;
    Client client(context, "127.0.0.1", 8081);
    client.start();

    std::string buffer("POST HTTP/1.1\rContent-Type: application/json\rHost: 127.0.0.1:8081\rContent-Length: 494\r\n\r\n "
                       "{\"classes\":[{\"id_griulbjilfevwoups\": 1,\"name\": \"WEB\",\"teacher\": \"Dinar\",\"count_students\": 21}, "
                       "{\"id_groups\": 2,\"name\": \"C++\",\"teacher\":\"Uliana\",\"count_students\": 21},{\"id_groups\": "
                       "1,\"name\": \"ALGORITHM\",\"teacher\": \"Krimov\",\"count_students\": 21}],\"classesNumber\": 0,\"students\": "
                       "[ [1, 0, 1], [1, 0, 1], [1, 0, 1], [1, 0, 1]],\"iterations\": 5, \"params\": {\"crossover\": \"default\", \"mutation\": "
                       "\"default\", \"selector\": \"default\", \"creator\": \"default\"}}");
    client.send(buffer);
    std::string str = client.read();
    int res = std::stoi(str.substr(9, 3));
    ASSERT_EQ(400, res);

    gen.turnOff();
    io_service.stop();
    tr.join();
}

// метод не разрешен
TEST(TEST_SERVER, response_reporter) {
    General gen = General(2);
    gen.turnOn();
    boost::asio::io_service io_service;
    Server s(io_service, 8081, &gen);
    std::thread tr([&] { io_service.run(); });

    boost::asio::io_context context;
    Client client(context, "127.0.0.1", 8081);
    client.start();

    std::string buffer("PATCH /status/b5fc218e-dd2hvhbjhberwhbrehbjrehjbrecfcfg HTTP/1.1\\rContent-Type: application/text\\rHost: 127.0.0.1:8081\\rContent-Length: 0\r");
    client.send(buffer);
    std::string str = client.read();
    int res = std::stoi(str.substr(9, 3));
    ASSERT_EQ(405, res);
    gen.turnOff();
    io_service.stop();
    tr.join();
}
// страница не найдена не верное API
TEST(TEST_SERVER, test_send_answer) {
    General gen = General(2);
    gen.turnOn();
    boost::asio::io_service io_service;
    Server s(io_service, 8081, &gen);
    std::thread tr([&] { io_service.run(); });

    boost::asio::io_context context;
    Client client(context, "127.0.0.1", 8081);
    client.start();

    std::string buffer("GET /what??/b5fc218e-dd2hvhbjhberwhbrehbjrehjbrecfcfg HTTP/1.1\\rContent-Type: application/text\\rHost: 127.0.0.1:8081\\rContent-Length: 0\r");
    client.send(buffer);
    std::string str = client.read();
    int res = std::stoi(str.substr(9, 3));
    ASSERT_EQ(404, res);
    gen.turnOff();
    io_service.stop();
    tr.join();
}