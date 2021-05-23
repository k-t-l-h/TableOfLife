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

    bool connect() override;

    Result Select(u::uuid) override;
    bool Insert(Result a) override;

    void create_tables(std::string table_name);
    void drop_table(std::string name);
private:

    std::string get_classes(std::vector<Classes> &classes);

    pqxx::result execute_stmt( std::string sql, std::string desc );

    std::string m_table_name;
    std::unique_ptr<pqxx::connection> db_connection;        //TODO unique_ptr
    std::mutex safety;
};



#endif //TABLEOFLIFE_DATABASE_H