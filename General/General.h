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
    std::mutex m;
    std::shared_ptr<Queue<Request>> ReqQueue;
    std::shared_ptr<Queue<Result>> ResQueue;
    std::shared_ptr<IDatabase> db;

    std::unique_ptr<Manager> man;
    std::unique_ptr<Reporter> rep;

    std::condition_variable condition;
    bool notified = false;

public:
    explicit General(int) {};

    void turnOn() {
        ReqQueue = std::make_shared<Queue<Request>>();
        ResQueue = std::make_shared<Queue<Result>>();


        man = std::make_unique<Manager>(ReqQueue,ResQueue);
        std::thread ma(&Manager::WorkCycle, man.get());
        ma.detach();

        db = std::make_shared<Database>();
        db->connect();

        rep = std::make_unique<Reporter>(ResQueue, db);

        std::thread r(&Reporter::WorkCycle, rep.get());
        r.detach();
    };

    void turnOff() {
        man->activate();
        rep->activate();
    };

    std::shared_ptr<IDatabase> ptr_db() {
        return db;
    }

    int getRequest(std::string request, u::uuid uuid) {
        std::unique_lock<std::mutex> lock(m);
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