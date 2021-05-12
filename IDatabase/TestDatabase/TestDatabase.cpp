#include "TestDatabase.h"

//int TestDatabase::TestDatabase() {}

bool TestDatabase::Insert(int u_id, const std::vector<int>& t_vec) {

    if ( this->id == u_id ) return false;

    data = t_vec;
    this->id = u_id;
    return true;
}

TestDatabase::~TestDatabase() {}

std::vector<int> TestDatabase::Select(int u_id) {
    if ( this->id != u_id ) return std::vector<int>();

    return this->data;
}