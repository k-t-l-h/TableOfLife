#include "TestDatabase.h"

#include <boost/uuid/uuid.hpp>            // uuid class

namespace u = boost::uuids;

//int TestDatabase::TestDatabase() {}

bool TestDatabase::Insert(u::uuid u_id, const std::vector<size_t>& t_vec) {

    if ( this->id == u_id ) return false;

    data = t_vec;
    this->id = u_id;
    return true;
}

bool TestDatabase::Insert( Result a) {

    if ( this->id == a.id ) return false;

    data = a.result;
    this->id = a.id;
    return true;
}


TestDatabase::~TestDatabase() {}

std::vector<size_t> TestDatabase::Select(u::uuid u_id) {
    if ( this->id != u_id ) return std::vector<size_t>();

    return this->data;
}