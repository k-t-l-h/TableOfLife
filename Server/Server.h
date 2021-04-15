#include <vector>
#include "../ParserToGA/ParserToGA.h"

#ifndef TABLEOFLIFE_SERVER_H
#define TABLEOFLIFE_SERVER_H


class Server {
public:
    std::string * returnBodyStr;
    std::string * DataJson;

    Server() : returnBodyStr(nullptr), DataJson(nullptr), status(true), port(8080), address("127.0.0.1") {};
    Server(const Server&) = delete;
    ~Server() = default;

    int SetUp();

    int ShutDown();

    int Run();

    int SendJson(int id);

    void responseReporter(int id);

    int SendAnswer();

private:
    bool status;
    uint16_t port;
    std::string address;

    std::string takeBody();
};

#endif //TABLEOFLIFE_SERVER_H
