#ifndef TABLEOFLIFE_TESTDATABASE_H
#define TABLEOFLIFE_TESTDATABASE_H

#include <vector>
#include "../IDatabase.h"
#include "../../Result/Result.h"
#include <boost/uuid/uuid.hpp>            // uuid class

namespace u = boost::uuids;

class TestDatabase: public IDatabase {
public:
    TestDatabase() = default;
    ~TestDatabase() override;

    bool connect() override;

    Result Select(u::uuid u_id) override;
    bool Insert(Result a) override;

private:
    std::vector<size_t> data = std::vector<size_t>();
    u::uuid id = u::uuid();
};


#endif //TABLEOFLIFE_TESTDATABASE_H