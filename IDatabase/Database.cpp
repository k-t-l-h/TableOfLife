#include "Database.h"

Database::Database() {}

Database::Database(sql *connect):connection(connect) {}

Database::~Database()  {}

bool Database::Insert(int id, const std::vector<size_t> &res)  {
    return true;
}
bool Database::Insert(Result a)  {
    return true;
}

std::vector<size_t> Select(int id) {
    return std::vector<size_t> ();
}