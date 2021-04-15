#include "../ParserToGA/ParserToGA.h"
#include "../Queue/Queue.h"


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

bool ParserToGA::validateData(std::string request) {
    return false;
}

bool ParserToGA::validateField(std::string request) {
    return false;
}

bool ParserToGA::validateIterations(std::string request) {
    return false;
}

bool ParserToGA::validateStrategy(std::string request) {
    return false;
}

void ParserToGA::WorkCycle(std::string * dataJson) {
    ParserToGA::setStatus();
    requestStr = *dataJson;

    ParserToGA::makeRequest();
    ParserToGA::validateData(requestStr);
    ParserToGA::validateField(requestStr);
    ParserToGA::validateIterations(requestStr);
    ParserToGA::validateStrategy(requestStr);
    ParserToGA::pushRequest();

    ParserToGA::setStatus();
}