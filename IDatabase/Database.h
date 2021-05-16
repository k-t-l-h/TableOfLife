#ifndef TABLEOFLIFE_DATABASE_H
#define TABLEOFLIFE_DATABASE_H

#include "IDatabase.h"
#include "../Result/Result.h"
#include <mutex>

class sql;

class Database: public IDatabase {
public:
    Database();
    Database(sql *connect);
    ~Database() override;

    std::vector<size_t> Select(int id) override;
    bool Insert(int id, const std::vector<size_t>&) override;
    bool Insert(Result a);

private:
    sql *connection;

    std::mutex safety;
};


#endif //TABLEOFLIFE_DATABASE_H