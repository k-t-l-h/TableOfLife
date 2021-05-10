//
// Created by slava on 15.04.2021.
//

#ifndef TABLEOFLIFE_IDATABASE_H
#define TABLEOFLIFE_IDATABASE_H
#include <vector>

struct Result;

class IDatabase {
public:
     virtual const std::vector<int>& Select(int id) =0;
     virtual void Insert(int id, const std::vector<int>&)=0;

};




#endif //TABLEOFLIFE_IDATABASE_H
