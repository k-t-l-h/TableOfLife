#ifndef TABLEOFLIFE_DATABASE_H
#define TABLEOFLIFE_DATABASE_H

#include "IDatabase.h"
class sql;

class Database: public IDatabase {
public:
    Database();
    Database(sql *connect);
    ~Database() override;

    const std::vector<int> Select(int id) override;
    void Insert(int id, const std::vector<int>&) override;

private:
    sql *connection;
};


#endif //TABLEOFLIFE_DATABASE_H
