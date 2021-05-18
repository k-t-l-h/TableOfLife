#include "Database.h"
#include <pqxx/pqxx>
#include <boost/uuid/uuid.hpp>
Database::Database() {}

Database::Database( pqxx::connection *connect ) : db_connection(connect) {}

Database::~Database()  {}

namespace u = boost::uuids;

bool Database::connect(){
    try
    {
        pqxx::connection C;
        std::cout << "Connected to " << C.dbname() << std::endl;
        pqxx::work W{C};

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
    return true;
}

std::vector<size_t> Database::Select(u::uuid u_id) {
    return std::vector<size_t>();
}

