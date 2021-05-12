#include "../Server/Server.h"
//#include "../Adapter/Adapter.cpp"
#include "../ParserToGA/ParserToGA.cpp"
#include "../ParserToGA/ParserToGA.h"
#include "../Request/Request.h"
#include "../Queue/Queue.cpp"
#include <memory>
#include <iostream>

int Server::SetUp() {
    ReQueue = std::make_shared<Queue<Request>>();

//    Server::Run();
    return 0;
}

int Server::ShutDown() {
    return 0;
}

int Server::Run() {
    return 0;
}

int Server::SendStrParser(int id) {
    return 0;
}


void Server::TakeAdapter(int id) {
    std::vector<int> mass;
    std::string json;
//    mass = Adapter::GetResult(id);
//    json = ParserToHuman::GetReadeble(mass);
}

void Server::PackReqParser() {
    // как-то будет вытягиваться строка из boost, а пока так
    returnBodyStr = "{\"id\": 45,\"classes\":[{\"id_groups\": 1,\"name\": \"WEB\",\"teacher\": \"Dinar\",\"count_students\": 21},{\"id_groups\":"
                                    " 2,\"name\": \"C++\",\"teacher\":\"Uliana\",\"count_students\": 21},{\"id_groups\": 1,\"name\": \"ALGORITHM\",\"teacher\": "
                                    "\"Krimov\",\"count_students\": 21}],\"classesNumber\": 0,\"students\": [ [1, 0, 1],[1, 0, 1],[1, 0, 1],[1, 0, 1]],\"iterations\": 5,"
                                    "\"params\": {\"crossover\": \"default\",\"mutation\": \"default\",\"selector\": \"default\",\"creator\": \"default\"}}";
    ParserToGA<Request> parse;
    Request req = *parse.WorkCycle(&returnBodyStr);
    ReQueue->Push(req);
}

int Server::SendAnswer() {
//    *DataJson = Server::takeBody();
//    ParserToGA<int> parser;
//    parser.Work(DataJson);
    return 0;
}
