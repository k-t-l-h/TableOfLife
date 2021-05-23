#ifndef TABLEOFLIFE_RESULT_H
#define TABLEOFLIFE_RESULT_H

#include <vector>
#include "../Request/Request.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp>

namespace u = boost::uuids;

struct Result {
    u::uuid id = u::nil_uuid();
    std::vector<size_t> result;
    std::vector<Classes> classes; // все занятия, а вних id группы
    size_t ClassesNumber;
};


#endif //TABLEOFLIFE_RESULT_H
