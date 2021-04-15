#ifndef TABLEOFLIFE_DATABASE_H
#define TABLEOFLIFE_DATABASE_H

#include "IDatabase.h"
class sql;

class Database: public IDatabase {
public:
    Database();
    Database(sql *connect);
    ~Database();

    int ** Select(int id);
    void Insert(int id, int **);

private:
    sql *connection;
};


#endif //TABLEOFLIFE_DATABASE_H
