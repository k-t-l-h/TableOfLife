//
// Created by slava on 14.04.2021.
//

#include "Database.h"

Database::Database() {}

Database::Database(sql *connect):connection(connect) {}

Database::~Database() override {}

void Database::Insert(int id, const std::vector<int>&res) {}

const std::vector<int>& Database::Select(int id) {}