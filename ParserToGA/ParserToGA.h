#include <iostream>
#include "../Request/Request.h"
#include "../Queue/Queue.h"

#ifndef TABLEOFLIFE_PARSERTOGA_H
#define TABLEOFLIFE_PARSERTOGA_H

template <typename T>
class ParserToGA {
public:
    ParserToGA(Queue<T> que) : workStatus(true), requestReq(nullptr), que(que) {};
    ParserToGA(const ParserToGA&) = delete;
    ~ParserToGA() = default;

    void WorkCycle(std::string * dataJson);

    void SetStatus();

    void PushRequest();

    void MakeRequest();


    bool workStatus;

private:
    Request * requestReq;
    std::string requestStr;
    Queue<T> que;

    bool validateData(std::string requestStr);

    bool validateField(std::string requestStr);

    bool validateIterations(std::string requestStr);

    bool validateStrategy(std::string requestStr);
};

#endif //TABLEOFLIFE_PARSERTOGA_H
