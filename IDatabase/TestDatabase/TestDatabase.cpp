#include "TestDatabase.h"

#include <boost/uuid/uuid.hpp>            // uuid class

namespace u = boost::uuids;

//int TestDatabase::TestDatabase() {}


bool TestDatabase::Insert( Result a) {

    if ( this->id == a.id ) return false;

    data = a.result;
    this->id = a.id;
    return true;
}

bool TestDatabase::connect(){
    return true;
}

TestDatabase::~TestDatabase() {}

Result TestDatabase::Select(u::uuid u_id) {

    Result res;
    res.id = u_id;
    res.result = std::vector<size_t>();
    return res;

}