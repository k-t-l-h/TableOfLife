#include <iostream>
#include "../Request/Request.h"
#include "../Queue/Queue.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <mutex>

#ifndef TABLEOFLIFE_PARSERTOGA_H
#define TABLEOFLIFE_PARSERTOGA_H

namespace pt = boost::property_tree;

template <typename T>
class ParserToGA {
public:
    ParserToGA() : req(new Request) {};
    ParserToGA(const ParserToGA&) = delete;
    ~ParserToGA() {
        delete req;
    };

    Request * WorkCycle(std::string * dataJson); // вызывается с сервера и кладется стринга json-а типа string

    bool SetStatus();

    Request * req;
private:
    std::string requestStr;
    std::mutex status_work;
    bool status_validation;

    void ParserToRequest(); // преобразование в тип Request

    void ParserValidate();

    bool validateClasses();

    bool validateStudents();
};

#endif //TABLEOFLIFE_PARSERTOGA_H
