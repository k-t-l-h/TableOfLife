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

    bool init( std::string, std::string );

    Result Select(u::uuid) override;
    bool Insert(Result a) override;


private:

    void create_db(std::string name);
    void create_table(std::string table_name);
    void drop_table(std::string name);

    std::string get_classes(std::vector<Classes> &classes);

    pqxx::result execute_stmt( std::string sql, std::string desc );

    std::string m_table_name;
    std::string db_name;
    std::unique_ptr<pqxx::connection> db_connection;

};



#endif //TABLEOFLIFE_DATABASE_H