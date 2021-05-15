#ifndef TABLEOFLIFE_DATABASE_H
#define TABLEOFLIFE_DATABASE_H

#include "IDatabase.h"
#include "../Result/Result.h"

class sql;

class Database: public IDatabase {
public:
    Database();
    Database(sql *connect);
    ~Database() override;

    std::vector<int> Select(int id) override;
    bool Insert(int id, const std::vector<int>&) override;
    bool Insert(Result a);

private:
    sql *connection;
};


#endif //TABLEOFLIFE_DATABASE_H