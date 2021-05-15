#include "Database.h"

Database::Database() {}

Database::Database(sql *connect):connection(connect) {}

Database::~Database()  {}

bool Database::Insert(int id, const std::vector<int> &res)  {
    return true;
}
bool Database::Insert(Result a)  {
    return true;
}

std::vector<int> Select(int id) {
    return std::vector<int> ();
}