#include <gtest/gtest.h>
#include "../General/General.h"
#include "../Server/Server.h"
#include "../ParserToGA/ParserToGA.h"
#include <boost/asio/io_service.hpp>
#include <../Client/Client.h>
#include <thread>
#include <string>
#include <unistd.h>

// ошибка в UUID
TEST(TEST_SERVER, error_uuid) {
    General gen = General(2);
    gen.turnOn();
    boost::asio::io_service io_service;
    Server s(io_service, 8081, &gen);
    std::thread tr([&] { io_service.run(); });

    boost::asio::io_context context;
    Client client(context, "127.0.0.1", 8081);
    client.start();

    std::string buffer("GET /status/b5fc218e-dd2hvhbjhberwhbrehbjrehjbrecfcfg HTTP/1.1\r\nContent-Type: application/text\r\nHost: 127.0.0.1:8081\r\nContent-Length: 0\r\n");
    client.send(buffer);
    std::string str = client.read();
    client.close();
    int res = std::stoi(str.substr(9, 3));
    ASSERT_EQ(400, res);
    gen.turnOff();
    io_service.stop();
    tr.join();
}

// кладет в очередь и проходит все проверки
TEST(TEST_SERVER, all_done_push) {
    General gen = General(2);
    gen.turnOn();
    boost::asio::io_service io_service;
    Server s(io_service, 8081, &gen);
    std::thread tr([&] { io_service.run(); });

    boost::asio::io_context context;
    Client client(context, "127.0.0.1", 8081);
    client.start();

    std::string buffer("POST /create/ HTTP/1.1\r\nContent-Type: application/json\r\nHost: 127.0.0.1:8081\r\nContent-Length: 494\r\n\r\n "
                       "{\"classes\":[{\"id_groups\": 1,\"name\": \"WEB\",\"teacher\": \"Dinar\",\"count_students\": 21}, "
                       "{\"id_groups\": 2,\"name\": \"C++\",\"teacher\":\"Uliana\",\"count_students\": 21},{\"id_groups\": "
                       "1,\"name\": \"ALGORITHM\",\"teacher\": \"Krimov\",\"count_students\": 21}],\"classesNumber\": 0,\"students\": "
                       "[ [1, 0, 1], [1, 0, 1], [1, 0, 1], [1, 0, 1]],\"iterations\": 5, \"params\": {\"crossover\": \"default\", \"mutation\": "
                       "\"default\", \"selector\": \"default\", \"creator\": \"default\"}}");
    client.send(buffer);
    std::string str = client.read();
    client.close();
    int res = std::stoi(str.substr(9, 3));
    ASSERT_EQ(201, res);

    gen.turnOff();
    io_service.stop();
    tr.join();
}

// не может распарсить json
TEST(TEST_SERVER, error_parse_json) {
    General gen = General(2);
    boost::asio::io_service io_service;
    gen.turnOn();
    Server s(io_service, 8081, &gen);
    std::thread tr([&] { io_service.run(); });

    boost::asio::io_context context;
    Client client(context, "127.0.0.1", 8081);
    client.start();

    std::string buffer("POST /create/ HTTP/1.1\r\nContent-Type: application/json\r\nHost: 127.0.0.1:8081\r\nContent-Length: 494\r\n\r\n "
                       "{\"classes\":[{\"id_griulbjilfevwoups\": 1,\"name\": \"WEB\",\"teacher\": \"Dinar\",\"count_students\": 21}, "
                       "{\"id_groups\": 2,\"name\": \"C++\",\"teacher\":\"Uliana\",\"count_students\": 21},{\"id_groups\": "
                       "1,\"name\": \"ALGORITHM\",\"teacher\": \"Krimov\",\"count_students\": 21}],\"classesNumber\": 0,\"students\": "
                       "[ [1, 0, 1], [1, 0, 1], [1, 0, 1], [1, 0, 1]],\"iterations\": 5, \"params\": {\"crossover\": \"default\", \"mutation\": "
                       "\"default\", \"selector\": \"default\", \"creator\": \"default\"}}");
    client.send(buffer);
    std::string str = client.read();
    client.close();
    int res = std::stoi(str.substr(9, 3));
    ASSERT_EQ(400, res);

    gen.turnOff();
    io_service.stop();
    tr.join();
}

// метод не разрешен
TEST(TEST_SERVER, error_methood) {
    General gen = General(2);
    gen.turnOn();
    boost::asio::io_service io_service;
    Server s(io_service, 8081, &gen);
    std::thread tr([&] { io_service.run(); });

    boost::asio::io_context context;
    Client client(context, "127.0.0.1", 8081);
    client.start();

    std::string buffer("PATCH /status/b5fc218e-dd2hvhbjhberwhbrehbjrehjbrecfcfg HTTP/1.1\r\nContent-Type: application/text\r\nHost: 127.0.0.1:8081\r\nContent-Length: 0\r");
    client.send(buffer);
    std::string str = client.read();
//    client.close();
    int res = std::stoi(str.substr(9, 3));
    ASSERT_EQ(405, res);
    gen.turnOff();
    io_service.stop();
    tr.join();
}

// страница не найдена не верное API
TEST(TEST_SERVER, invalid_url) {
    General gen = General(2);
    gen.turnOn();
    boost::asio::io_service io_service;
    Server s(io_service, 8081, &gen);
    std::thread tr([&] { io_service.run(); });

    boost::asio::io_context context;
    Client client(context, "127.0.0.1", 8081);
    client.start();

    std::string buffer("GET /what/b5fc218e-dd2hvhbjhberwhbrehbjrehjbrecfcfg HTTP/1.1\r\nContent-Type: application/text\r\nHost: 127.0.0.1:8081\r\nContent-Length: 0\r\n");
    client.send(buffer);
    std::string str = client.read();
    client.close();
    int res = std::stoi(str.substr(9, 3));
    ASSERT_EQ(404, res);
    gen.turnOff();
    io_service.stop();
    tr.join();
}

// кладет в очередь и проходит все проверки и потом возвращает результат
TEST(TEST_SERVER, all_done_push_and_get) {
    General gen = General(2);
    gen.turnOn();
    boost::asio::io_service io_service;
    Server s(io_service, 8081, &gen);
    std::thread tr([&] { io_service.run(); });

    boost::asio::io_context context;
    Client client_post(context, "127.0.0.1", 8081);
    client_post.start();
    // метод POST
    std::string post("POST /create/ HTTP/1.1\r\nContent-Type: application/json\r\nHost: 127.0.0.1:8081\r\nContent-Length: 494\r\n\r\n "
                       "{\"classes\":[{\"id_groups\": 1,\"name\": \"WEB\",\"teacher\": \"Dinar\",\"count_students\": 21}, "
                       "{\"id_groups\": 2,\"name\": \"C++\",\"teacher\":\"Uliana\",\"count_students\": 21},{\"id_groups\": "
                       "1,\"name\": \"ALGORITHM\",\"teacher\": \"Krimov\",\"count_students\": 21}],\"classesNumber\": 0,\"students\": "
                       "[ [1, 0, 1], [1, 0, 1], [1, 0, 1], [1, 0, 1]],\"iterations\": 5, \"params\": {\"crossover\": \"default\", \"mutation\": "
                       "\"default\", \"selector\": \"default\", \"creator\": \"default\"}}");
    client_post.send(post);
    std::string post_str = client_post.read();
    client_post.close();
    int post_res = std::stoi(post_str.substr(9, 3));
    ASSERT_EQ(201, post_res);
    std::string str_uuid = post_str.substr(post_str.find("UUID") + 8, 36);


// метод GET
    sleep(5); // ГА может долго думать
    Client client_get(context, "127.0.0.1", 8081);
    client_get.start();
    std::string get("GET /status/" + str_uuid +" HTTP/1.1\r\nContent-Type: application/text\r\nHost: 127.0.0.1:8081\r\nContent-Length: 0\r\n"
    );
    client_get.send(get);
    std::string get_str = client_get.read();
    client_get.close();
    int get_res = std::stoi(get_str.substr(9, 3));
    ASSERT_EQ(200, get_res);

    gen.turnOff();
    io_service.stop();
    tr.join();
}