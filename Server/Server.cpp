#include "Server.h"
#include <iostream>

int Server::SetUp() {
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
    Server::SendJson(id);
}

std::string Server::takeBody() {

    return *returnBodyStr;
}

void Server::SendAnswer() {
    *DataJson = Server::takeBody()
    ParseToGA::Work(DataJson);
}
