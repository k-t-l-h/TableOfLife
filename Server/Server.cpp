#include "../Server/Server.h"
//#include "../Adapter/Adapter.cpp"
#include "../ParserToGA/ParserToGA.cpp"
#include "../ParserToGA/ParserToGA.h"
#include "../Request/Request.h"
#include "../Queue/Queue.cpp"
#include "../Manager/Manager.h"
#include "../Result/Result.h"
#include <memory>
#include <iostream>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>

namespace u = boost::uuids;

int Server::SetUp() {
    ReqQueue = std::make_shared<Queue<Request>>();
    ResQueue = std::make_shared<Queue<Result>>();
    Manager manager(ReqQueue, ResQueue);


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
    returnBodyStr = "{\"classes\":[{\"id_groups\": 1,\"name\": \"WEB\",\"teacher\": \"Dinar\",\"count_students\": 21},{\"id_groups\":"
                                    " 2,\"name\": \"C++\",\"teacher\":\"Uliana\",\"count_students\": 21},{\"id_groups\": 1,\"name\": \"ALGORITHM\",\"teacher\": "
                                    "\"Krimov\",\"count_students\": 21}],\"classesNumber\": 0,\"students\": [ [1, 0, 1],[1, 0, 1],[1, 0, 1],[1, 0, 1]],\"iterations\": 5,"
                                    "\"params\": {\"crossover\": \"default\",\"mutation\": \"default\",\"selector\": \"default\",\"creator\": \"default\"}}";
    ParserToGA<Request> parse;

    if (parse.WorkCycle(&returnBodyStr) == nullptr) {
        printf("Not valid"); // иначе возвращаем пользователю ошибку
    } else {
        Request req = *parse.req;
        u::random_generator gen;
        req.id = gen();
        ReQueue->Push(req);
    }
}

int Server::SendAnswer() {
//    *DataJson = Server::takeBody();
//    ParserToGA<int> parser;
//    parser.Work(DataJson);
    return 0;
}
