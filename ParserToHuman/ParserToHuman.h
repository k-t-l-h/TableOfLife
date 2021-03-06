#ifndef TABLEOFLIFE_PARSERGATOHUMAN_H
#define TABLEOFLIFE_PARSERGATOHUMAN_H

#include "../Result/Result.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/uuid/uuid_io.hpp>

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


std::string ParserToHuman::GetReadable( Result res ) {

    root.put("uuid",  std::string(boost::uuids::to_string(res.id)));

    pt::ptree classes;
    for(auto cls: res.classes){
        pt::ptree sub_classes;
        sub_classes.put("name", cls.name);
        sub_classes.put("teacher", cls.teacher);
        sub_classes.put("id_group", std::to_string(cls.id_groups));
        classes.add_child("sub_class",sub_classes);
    }

    root.add_child("classes", classes);

    std::stringstream arr;

    size_t students_count = res.result.size()/res.ClassesNumber;

    pt::ptree matrix_node;
    for (int i = 0; i < students_count ; i++)
    {
        pt::ptree row;
        for (int j = 0; j < res.ClassesNumber; j++)
        {
            // Create an unnamed value
            pt::ptree cell;
            cell.put_value(res.result[i*j]);
            // Add the value to our row
            row.push_back(std::make_pair("", cell));
        }
        // Add the row to our matrix
        matrix_node.push_back(std::make_pair("", row));
    }

    root.add_child("solution", matrix_node);

    std::stringstream s;
    pt::write_json(s, root);

    return s.str();
}


#endif //TABLEOFLIFE_PARSERGATOHUMAN_H