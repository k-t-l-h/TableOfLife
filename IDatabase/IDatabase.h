//
// Created by slava on 15.04.2021.
//

#ifndef TABLEOFLIFE_IDATABASE_H
#define TABLEOFLIFE_IDATABASE_H


class IDatabase {
public:

    virtual ~IDatabase() = 0 ;

    virtual const std::vector<int>& Select(int id) = 0;
    virtual void Insert(int id, const vector<int>&) = 0;

};


#endif //TABLEOFLIFE_IDATABASE_H
