//
// Created by slava on 15.04.2021.
//

#ifndef TABLEOFLIFE_IDATABASE_H
#define TABLEOFLIFE_IDATABASE_H


class IDatabase {
public:
    IDatabase();
    virtual ~IDatabase();

    virtual int ** Select(int id);
    virtual void Insert(int id, int **);

};


#endif //TABLEOFLIFE_IDATABASE_H
