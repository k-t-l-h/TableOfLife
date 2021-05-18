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

    std::vector<size_t> Select(u::uuid u_id) override;
    bool Insert(u::uuid id, const std::vector<size_t>&) override;
    bool Insert(Result a) override;

private:
    std::vector<size_t> data = std::vector<size_t>();
    u::uuid id = u::uuid();
};


#endif //TABLEOFLIFE_TESTDATABASE_H