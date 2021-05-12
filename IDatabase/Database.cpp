//
// Created by slava on 14.04.2021.
//

#include "Database.h"

Database::Database() {}

Database::Database(sql *connect):connection(connect) {}

Database::~Database() override {}

bool Database::Insert(int id, const std::vector<int> &res) override {}

std::vector<int> Select(int id) override {}