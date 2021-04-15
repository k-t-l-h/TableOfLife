//
// Created by slava on 14.04.2021.
//

#include "Database.h"

Database::Database() {}

Database::Database(sql *connect):connection(connect) {}

Database::~Database() {}

void Database::Insert(int id, int **arr) {}

bool Database::Select(const char *options) {}