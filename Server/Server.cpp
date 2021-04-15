#include "Server.h"
#include "../Adapter/Adapter.cpp"
#include "../ParserToGA/ParserToGA.cpp"
#include "../ParserToHuman/ParserToHuman.cpp"
#include <iostream>

int Server::SetUp() {
    Server::Run();
    return 0;
}

int Server::ShutDown() {
    return 0;
}

int Server::Run() {
    return 0;
}

int Server::SendJson(int id) {
    return 0;
}


void Server::responseReporter(int id) {
    std::vector<int> mass;
    std::string json;
    mass = Adapter::GetResult(id);
    json = ParserToHuman::GetReadeble(mass);

    Server::SendJson(id);
}

std::string Server::takeBody() {

    return *returnBodyStr;
}

int Server::SendAnswer() {
    *DataJson = Server::takeBody();
    ParserToGA parser;
    parser.Work(DataJson);
    return 0;
}
