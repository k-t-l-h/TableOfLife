#include <vector>
#include "../ParserToGA/ParserToGA.h"
#include "../Request/Request.h"

#ifndef TABLEOFLIFE_SERVER_H
#define TABLEOFLIFE_SERVER_H


class Server {
public:
    std::string returnBodyStr;
    std::string * DataJson;
    std::shared_ptr<Queue<Request>> ReQueue;
//    std::shared_ptr<Queue<Result>> ResQueue;

    Server() : DataJson(nullptr), status(true), port(8080), address("127.0.0.1") {};
    Server(const Server&) = delete;
    ~Server() = default;

    int SetUp(); // всем рассылаю shared_ptr

    int ShutDown();

    int Run(); // слушает реквесты

    int SendStrParser(int id); // отправка json пользователю

    void TakeAdapter(int id); //

    int SendAnswer();

    void PackReqParser();

private:

    bool status;
    uint16_t port;
    std::string address;

};

#endif //TABLEOFLIFE_SERVER_H
