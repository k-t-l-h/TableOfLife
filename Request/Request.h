#include <iostream>
#include <vector>

#ifndef TABLEOFLIFE_REQUEST_H
#define TABLEOFLIFE_REQUEST_H

class Request {
public:
    Request() = default;
    Request(const Request&) = delete;

    int id;
    bool field;
    time_t timeIterations;
    std::string strategy;
    std::vector <int> data;

    ~Request() = default;
};

#endif //TABLEOFLIFE_REQUEST_H
