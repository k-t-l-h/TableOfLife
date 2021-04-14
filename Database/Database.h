#ifndef TABLEOFLIFE_DATABASE_H
#define TABLEOFLIFE_DATABASE_H

class sql;

class Database {
public:
    Database();
    Database(sql *connect);
    ~Database();

    bool Select(const char * options);
    void Insert(int id, int **);

private:
    sql *connection;
};


#endif //TABLEOFLIFE_DATABASE_H
