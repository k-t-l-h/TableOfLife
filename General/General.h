#ifndef TABLEOFLIFE_GENERAL_H
#define TABLEOFLIFE_GENERAL_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "../Queue/Queue.h"
#include "../Request/Request.h"
#include "../Result/Result.h"
#include "../Manager/Manager.cpp"
#include "../Reporter/Reporter.cpp"
#include "../ParserToGA/ParserToGA.h"
#include <../IDatabase/Database.h>
#include <algorithm>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include <memory>
#include <string>

#define OK 0
#define ERROR -1

class Session;

class General {
private:
//    std::mutex m;
    std::shared_ptr<Queue<Request>> ReqQueue;
    std::shared_ptr<Queue<Result>> ResQueue;
    Manager * man;
    Reporter * rep;
    std::condition_variable condition;
    bool notified = false;
//    std::shared_ptr<Parser> parser;

public:
    explicit General(int) {};

    void turnOn() {
//        auto DB = std::shared_ptr<IDatabase>(new TestDatabase);
        ReqQueue = std::make_shared<Queue<Request>>();
        ResQueue = std::make_shared<Queue<Result>>();

        Manager manager(ReqQueue,ResQueue);
        man = &manager;
        std::thread m(&Manager::WorkCycle, &manager);
        m.detach();
        std::shared_ptr<Database> db = std::make_shared<Database>();

        Reporter reporter(ResQueue, db);
//        rep = &reporter;
//        std::thread r(&Reporter::WorkCycle, &reporter);
//        r.detach();
        // Потом будет что-то еще

    };

    void turnOff() {
        man->activate();
        rep->activate();

    };

    int getRequest(std::string request, u::uuid uuid) {
//        std::unique_lock<std::mutex> lock(m);
        ParserToGA<Request> parse;

        if (parse.WorkCycle(&request) == nullptr)
            return ERROR; // иначе возвращаем ошибку

        Request req = *parse.req;
        req.id = uuid;
        ReqQueue->Push(req);

        notified = true;
        condition.notify_one();
        return OK;
    };
};

#endif //TABLEOFLIFE_GENERAL_H
