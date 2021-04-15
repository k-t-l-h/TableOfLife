#include <iostream>
#include <vector>

#ifndef TABLEOFLIFE_REQUEST_H
#define TABLEOFLIFE_REQUEST_H


class Request {
public:
    Request() = default;
    ~Request() = default;
    Request(const Request&) = delete;

    int id;
    int type; //возможно тут enum
    size_t countActive; //сколько активностей
    time_t timeIterations; //если ограничение по времени
    size_t numIterations; //если ограничение по числу
    float fitness;
    //это нужно для билдера ГА
    std::tuple<std::string, std::string, std::string, std::string> params;
    std::vector <std::vector<int>> data;
};

#endif //TABLEOFLIFE_REQUEST_H
