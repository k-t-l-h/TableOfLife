#include <iostream>
#include <Request.h>

#ifndef TABLEOFLIFE_PARSERTOGA_H
#define TABLEOFLIFE_PARSERTOGA_H

class ParserToGA {
public:
    ParserToGA() : workStatus(nullptr), requestReq(nullptr) {};
    ParserToGA(const ParserToGA&) = delete;

    void Work(std::string * dataJson);

    void setStatus();

    void pushRequest();

    void makeRequest();

    ~ParserToGA() = default;

private:
    bool * workStatus;
    Request * requestReq;
    std::string requestStr;

    bool validateData(std::string request);

    bool validateField(std::string request);

    bool validateIterations(std::string request);

    bool validateStrategy(std::string request);
};

#endif //TABLEOFLIFE_PARSERTOGA_H
