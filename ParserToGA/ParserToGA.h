#include <iostream>
#include "../Request/Request.h"

#ifndef TABLEOFLIFE_PARSERTOGA_H
#define TABLEOFLIFE_PARSERTOGA_H

class ParserToGA {
public:
    bool * workStatus;
    ParserToGA() : workStatus(nullptr), requestReq(nullptr) {};
    ParserToGA(const ParserToGA&) = delete;

    void WorkCycle(std::string * dataJson);

    void SetStatus();

    void PushRequest();

    void MakeRequest();

    ~ParserToGA() = default;

private:
    Request * requestReq;
    std::string requestStr;

    bool validateData(std::string requestStr);

    bool validateField(std::string requestStr);

    bool validateIterations(std::string requestStr);

    bool validateStrategy(std::string requestStr);
};

#endif //TABLEOFLIFE_PARSERTOGA_H
