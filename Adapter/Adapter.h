
#ifndef TABLEOFLIFE_ADAPTER_H
#define TABLEOFLIFE_ADAPTER_H

#include <memory>
#include <vector>
#include <shared_mutex>
#include <boost/uuid/uuid.hpp>            // uuid class

namespace u = boost::uuids;

class IDatabase;

class Adapter {
public:
    Adapter();
    explicit Adapter(std::shared_ptr<IDatabase> t_db);
    ~Adapter();

    const std::vector<size_t> GetResult(u::uuid) const;

private:
    Adapter(const Adapter &a) = delete;
    Adapter& operator=(const Adapter &a) = delete;

    //mutable std::shared_mutex mtx;
    std::shared_ptr<IDatabase> db;
};


#endif //TABLEOFLIFE_ADAPTER_H