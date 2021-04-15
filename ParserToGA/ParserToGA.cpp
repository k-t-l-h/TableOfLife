#include "ParserToGA.h"
#include "Queue.h"
//#include "Request.h"

void ParserToGA::Work(std::string *dataJson) {
    ParserToGA::setStatus();

    ParserToGA::makeRequest();
    ParserToGA::validateData(requestStr);
    ParserToGA::validateField(requestStr);
    ParserToGA::validateIterations(requestStr);
    ParserToGA::validateStrategy(requestStr);
    ParserToGA::pushRequest();

    ParserToGA::setStatus();
}

void ParserToGA::setStatus() {
    *workStatus = false;
}

void ParserToGA::pushRequest() {
    Queue<Request>::Push(requestReq);
}

void ParserToGA::makeRequest() {
    Request req;
    *requestReq = req;
}

bool ParserToGA::validateData(std::string requestStr) {
    return false;
}

bool ParserToGA::validateField(std::string requestStr) {
    return false;
}

bool ParserToGA::validateIterations(std::string requestStr) {
    return false;
}

bool ParserToGA::validateStrategy(std::string requestStr) {
    return false;
}