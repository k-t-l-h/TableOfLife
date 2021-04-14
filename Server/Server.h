#include <vector>

#ifndef TABLEOFLIFE_SERVER_H
#define TABLEOFLIFE_SERVER_H


class Server {
public:
    Server() : returnBodyStr(nullptr), DataJson(nullptr), status(true) {};
    Server(const Server&) = delete;

    int SetUp();

    int ShutDown();

    int Run();

    int SendJson(int id);

    void responseReporter(int id);

    void SendAnswer();

    ~Server() = default;

private:
    std::string * returnBodyStr;
    std::string * DataJson;
    bool status;

    std::string takeBody();
};

#endif //TABLEOFLIFE_SERVER_H
