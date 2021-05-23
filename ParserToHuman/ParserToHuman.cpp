#include "ParserToHuman.h"
#include <boost/uuid/uuid_io.hpp>
#include <iostream>

namespace pt = boost::property_tree;

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
    for (int i = 0; i < res.ClassesNumber; i++)
    {
        pt::ptree row;
        for (int j = 0; j < students_count; j++)
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
