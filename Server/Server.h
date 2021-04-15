#include <vector>
#include "ParserToGA.h"

#ifndef TABLEOFLIFE_SERVER_H
#define TABLEOFLIFE_SERVER_H


class Server {
public:
    std::string * returnBodyStr;
    std::string * DataJson;
    uint16_t port;
    std::string address;
    Server() : returnBodyStr(nullptr), DataJson(nullptr), status(true), port(8080) {};
    Server(const Server&) = delete;

    int SetUp();

    int ShutDown();

    int Run();

    int SendJson(int id);

    void responseReporter(int id);

    int SendAnswer();

    ~Server() = default;

private:
    bool status;

    std::string takeBody();
};

#endif //TABLEOFLIFE_SERVER_H
