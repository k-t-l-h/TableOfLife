
#ifndef TABLEOFLIFE_ADAPTER_H
#define TABLEOFLIFE_ADAPTER_H

#include <memory>
#include <vector>
#include <shared_mutex>
#include <boost/uuid/uuid.hpp>            // uuid class

#include "../Result/Result.h"

namespace u = boost::uuids;

class IDatabase;

class Adapter {
public:
    Adapter();
    explicit Adapter(std::shared_ptr<IDatabase> t_db);
    ~Adapter();

    Result GetResult(u::uuid);

private:
    Adapter(const Adapter &a) = delete;
    Adapter& operator=(const Adapter &a) = delete;

    //mutable std::shared_mutex mtx;
    std::shared_ptr<IDatabase> db;
};


#endif //TABLEOFLIFE_ADAPTER_H