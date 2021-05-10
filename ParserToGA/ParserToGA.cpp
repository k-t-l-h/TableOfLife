#include "../ParserToGA/ParserToGA.h"
#include "../Queue/Queue.h"


template <typename T> void ParserToGA<T>::SetStatus() {
    workStatus = false;
}

template <typename T> void ParserToGA<T>::PushRequest() {
    que->Push(requestReq);
}

template <typename T> void ParserToGA<T>::MakeRequest() {
    Request req;
    requestReq = &req;
}

template <typename T> bool ParserToGA<T>::validateData(std::string request) {
    return false;
}

template <typename T> bool ParserToGA<T>::validateField(std::string request) {
    return false;
}

template <typename T> bool ParserToGA<T>::validateIterations(std::string request) {
    return false;
}

template <typename T> bool ParserToGA<T>::validateStrategy(std::string request) {
    return false;
}

template <typename T> void ParserToGA<T>::WorkCycle(std::string * dataJson) {
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