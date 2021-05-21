#include "Database.h"
#include <pqxx/pqxx>
#include <boost/uuid/uuid.hpp>
#include <memory>

Database::Database() {}

Database::Database( std::unique_ptr<pqxx::connection> &&connect ) : db_connection(std::move(connect)) {}

Database::~Database()  {}

namespace u = boost::uuids;

bool Database::connect(){
    try
    {
        db_connection = std::make_unique<pqxx::connection>();
        std::cout << "Connected to " << db_connection->dbname() << std::endl;
        pqxx::work W{*db_connection};

        pqxx::result R{W.exec("CREATE TABLE students")};


        W.exec0("UPDATE employee SET salary = salary*2");

        std::cout << "Making changes definite: ";
        W.commit();
        std::cout << "OK.\n";

        return true;
    }
    catch (std::exception const &e)
    {
        std::cerr << e.what() << '\n';

        return false;
    }
}

bool Database::Insert(u::uuid id, const std::vector<size_t> &res)  {
    return true;
}
bool Database::Insert(Result a)  {
    pqxx::work W{*db_connection};

    W.exec0("my insert query");

    W.commit();

    return true;
}

std::vector<size_t> Database::Select(u::uuid u_id) {
    return std::vector<size_t>();
}

