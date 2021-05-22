#include "Database.h"
#include <pqxx/pqxx>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <memory>
#include <numeric>
#include <sstream>
#include <iostream>

Database::Database() {}

Database::Database( std::unique_ptr<pqxx::connection> &&connect ) : db_connection(std::move(connect)) {}

Database::~Database()  {}

namespace u = boost::uuids;

bool Database::connect(){
    try
    {
        db_connection = std::make_unique<pqxx::connection>("postgresql://postgres@localhost/solution");
        std::cout << "Connected to " << db_connection->dbname() << std::endl;
        std::cout << "OK.\n";
        return true;
    }
    catch (std::exception const &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}


bool Database::Insert(Result a)  {

    std::string array = std::accumulate(a.result.begin(), a.result.end(), std::string(), [](const std::string &str, int i){return str + std::to_string(i) + ",";});
    array.erase(array.size()-1);
    std::string insert_string = std::string("INSERT INTO ") + m_table_name + std::string(" VALUES ('") + std::string(boost::uuids::to_string(a.id)) + std::string("',") + std::string("'{") + array + std::string("}');"); //TODO убери нолик!!!!!!!!!!!!
    execute_stmt(insert_string, "insert into solution");
    return true;
}

Result Database::Select(u::uuid u_id) {
    std::string select_str = std::string("SELECT solution_array FROM ") + m_table_name + std::string(" WHERE ") + m_table_name + std::string(".user_id ='") + std::string(boost::uuids::to_string(u_id)) + std::string("';");
    pqxx::result r = execute_stmt(select_str, "select query");
    Result res;

    std::string translator;
    for (pqxx::result::const_iterator c = r.begin(); c != r.end(); ++c) {
        std::cout << "Solution = " << c[0].as<std::string>() << std::endl;
        translator += c[0].as<std::string>();
    }

    //TODO до конца заполнить res и по человечески заполнить вектор
    res.id=u_id;


    for(auto a: translator){
        if (a != ',' && a != '{' && a != '}') res.result.push_back(a - '0');
    }

    return res;
}


void Database::drop_table(std::string name){
    std::string create_table = std::string("DROP TABLE IF EXISTS ")+ name + std::string(";");
    execute_stmt(create_table, "drop table solution");
}

void Database::create_tables(std::string table_name){
    std::string create_table = std::string("CREATE TABLE ")+ table_name + std::string(" (") + std::string("user_id TEXT ,solution_array INTEGER[]);");
    m_table_name = table_name;
    execute_stmt(create_table, "create table solution");
}



pqxx::result Database::execute_stmt(std::string sql, std::string desc) {
    pqxx::work w(*db_connection);
    pqxx::result r;
    try {
        r = w.exec(sql.c_str());
        w.commit();
    } catch (const std::exception &e) {
        w.abort();
        std::cerr << "Error: " << desc << ": " << e.what() << std::endl;
        throw;
    }
    //  std::cerr << "Success: " << desc << std::endl;
    return r;
}