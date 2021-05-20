#ifndef TABLEOFLIFE_DATABASE_H
#define TABLEOFLIFE_DATABASE_H

#include "IDatabase.h"
#include "../Result/Result.h"
#include <mutex>
#include <pqxx/pqxx>
#include <boost/uuid/uuid.hpp>
#include <memory>

namespace u = boost::uuids;

class Database: public IDatabase {
public:
    Database();
    Database(std::unique_ptr<pqxx::connection> &&db_connection);
    ~Database() override;

    bool connect();

    std::vector<size_t> Select(u::uuid) override;
    bool Insert(u::uuid id, const std::vector<size_t>&) override;
    bool Insert(Result a) override;

private:

    std::unique_ptr<pqxx::connection> db_connection;        //TODO unique_ptr
    std::mutex safety;
};



#endif //TABLEOFLIFE_DATABASE_H