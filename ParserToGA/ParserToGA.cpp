#include "../ParserToGA/ParserToGA.h"
#include "../Queue/Queue.h"


void ParserToGA::SetStatus() {
    *workStatus = false;
}

void ParserToGA::PushRequest() {
    Queue<Request>::Push(requestReq);
}

void ParserToGA::MakeRequest() {
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
    ParserToGA::SetStatus();
    requestStr = *dataJson;

    ParserToGA::MakeRequest();
    ParserToGA::validateData(requestStr);
    ParserToGA::validateField(requestStr);
    ParserToGA::validateIterations(requestStr);
    ParserToGA::validateStrategy(requestStr);
    ParserToGA::PushRequest();

    ParserToGA::SetStatus();
}