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
#include "../IDatabase/TestDatabase/TestDatabase.h"
#include <algorithm>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include <memory>
#include <string>

class Session;

class General {
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
        ParserToGA<Request> parse;

//        Reporter reporter(ResQueue, DB);
//        rep = &reporter;
//        std::thread r(&Reporter::WorkCycle, &reporter);
//        r.detach();
        // Потом будет что-то еще

    };

    void turnOff() {
        man->activate();
        rep->activate();
//        parser->setStatus(false);
//        manager->setWorkingState(false);
//        reporter->setWorkingState(false);
        std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    };

    void getRequest(std::string request) {
        std::unique_lock<std::mutex> lock(m);
        ParserToGA<Request> parse;

        if (parse.WorkCycle(&request) == nullptr) {
            printf("Not valid"); // иначе возвращаем пользователю ошибку
        } else {
            Request req = *parse.req;
            u::random_generator gen;
            req.id = gen();
            ReqQueue->Push(req);
        }
//        std::move
        notified = true;
        condition.notify_one();
    };

    std::pair<bool, std::string> sendAnswer(int id) {
//        std::string result;
//        if (!db->select(id, result)) {
//            return {false, ""};
//        }
        return {true, nullptr};
    };

//    void addSession(boost::shared_ptr<Session> session) {
//        sessions.push_back(session);
//    };
//
//    void removeSession(boost::shared_ptr<Session> session) {
//        auto it = std::find(sessions.begin(), sessions.end(), session);
//        if (it != sessions.end())
//            sessions.erase(it);
//    };
//
//    std::pair<bool, boost::shared_ptr<Session>> findSession(boost::shared_ptr<Session> session) {
//        auto it = std::find(sessions.begin(), sessions.end(), session);
//        if (it != sessions.end()) {
//            return {true, *it};
//        }
//        return {false, nullptr};
//    };

private:
    std::mutex m;
    std::shared_ptr<Queue<Request>> ReqQueue;
    std::shared_ptr<Queue<Result>> ResQueue;
    std::shared_ptr<IDatabase> db;
    Manager * man;
    Reporter * rep;
    std::condition_variable condition;
    bool notified = false;
//    std::shared_ptr<Parser> parser;
    std::vector<std::thread> threads;

    std::vector<boost::shared_ptr<Session>> sessions;
};

#endif //TABLEOFLIFE_GENERAL_H
