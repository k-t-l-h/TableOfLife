#ifndef TABLEOFLIFE_PARSERGATOHUMAN_H
#define TABLEOFLIFE_PARSERGATOHUMAN_H

#include "../Result/Result.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

// Short alias for this namespace
namespace pt = boost::property_tree;

class json;

class ParserToHuman {
public:
    ParserToHuman() = default;
    ~ParserToHuman() = default;

    std::string GetReadable( Result res );
private:
    pt::ptree root;
    ParserToHuman(const ParserToHuman &a) = delete;
    ParserToHuman& operator=(const ParserToHuman &a) = delete;

};


#endif //TABLEOFLIFE_PARSERGATOHUMAN_H
