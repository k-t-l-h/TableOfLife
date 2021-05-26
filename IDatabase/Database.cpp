#include "Database.h"
#include <pqxx/pqxx>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <memory>
#include <numeric>
#include <sstream>
#include <iostream>

//времено захаркожено, будем потом итать конфиг
Database::Database() {
    db_name = "solution";
    m_table_name = "TestSolution";
}

Database::Database( std::unique_ptr<pqxx::connection> &&connect ) : db_connection(std::move( connect )) {}

Database::~Database()  {}

namespace u = boost::uuids;

bool Database::connect(){
    try
    {
        db_connection = std::make_unique<pqxx::connection>(std::string("postgresql://postgres@localhost/") + std::string(db_name));

        if( !db_connection )
            throw std::string( "some trouble with connection to db" );

        std::cout << "Connected to " << db_connection->dbname() << std::endl;
        std::cout << "OK.\n";

        return true;
    }
    catch ( std::exception const &e )
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    catch ( std::string trouble ) {
        std::cerr << trouble << std::endl;
        return false;
    }
}


bool Database::Insert( Result a )  {

    std::string classes_string = get_classes( a.classes );

    std::string array = std::accumulate(a.result.begin(), a.result.end(), std::string(), [](const std::string &str, int i){return str + std::to_string(i) + ",";});
    array.erase( array.size() - 1 );

    std::string insert_string = std::string("INSERT INTO ") + m_table_name + std::string(" VALUES ('") + std::string(boost::uuids::to_string(a.id)) + std::string("',") + std::string("'{") + array + std::string("}','") + std::to_string(a.classes.size()) + std::string("','") + classes_string + std::string("');");

    execute_stmt(insert_string, "insert into solution");
    return true;
}

Result Database::Select( u::uuid u_id ) {
    std::string select_str = std::string("SELECT solution_array,classes_number,classes FROM ") + m_table_name + std::string(" WHERE ") + m_table_name + std::string(".user_id ='") + std::string(boost::uuids::to_string(u_id)) + std::string("';");
    pqxx::result r = execute_stmt(select_str, "select query");

    if( r.size() == 0 ){
        return {};
    }

    Result res;
    std::string translator;
    std::string temp;

    for (pqxx::result::const_iterator c = r.begin(); c != r.end(); ++c) {
        std::cout << "Solution = " << c[0].as<std::string>() << std::endl;
        std::cout << "Classes info = " << c[2].as<std::string>() << std::endl;
        temp += c[2].as<std::string>();
        translator += c[0].as<std::string>();
    }

    std::stringstream class_fill(temp);

    for(size_t i = 0; i < r.begin()[1].as<int>(); ++i){
        Classes cls_m;
        class_fill >> cls_m.name >> cls_m.teacher >> cls_m.id_groups;
        res.classes.push_back(cls_m);
    }

    res.id = u_id;
    res.ClassesNumber = r.begin()[1].as<size_t>();
    for(auto a: translator){
        if (a != ',' && a != '{' && a != '}') res.result.push_back(a - '0');
    }

    return res;
}


void Database::drop_table( std::string name ){
    std::string create_table = std::string("DROP TABLE IF EXISTS ") + name + std::string(";");
    execute_stmt(create_table, "drop table solution");
}

void Database::create_table( std::string table_name ){
    std::string create_table = std::string("CREATE TABLE IF NOT EXISTS ") + table_name + std::string(" (") + std::string("user_id TEXT ,solution_array INTEGER[], classes_number INTEGER, classes TEXT);");
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
    return r;
}

std::string Database::get_classes(std::vector<Classes> &classes) {
    std::stringstream out_string;
    for(auto cls: classes){
        out_string << cls.name << '\t' << cls.teacher << '\t' << cls.id_groups << '\t';
    }
    return out_string.str();
}



void Database::create_db( std::string name ){
    try
    {
//зашли от имени postgres
        const std::string str_local = "user='postgres' password='111' host='localhost' port='5432' dbname='postgres'";
        pqxx::connection con(str_local);
        pqxx::nontransaction query(con, "Sample");
        pqxx::result res2 = query.exec(" DROP USER TestUser; ");
        pqxx::result res = query.exec(" CREATE USER TestUser WITH PASSWORD 'qwerty'; ");
    }
    catch(const pqxx::failure& e)
    {
        std::cout<<"problem: "<<e.what()<<std::endl;
    }

    try
    {
        const std::string str_local = "user='postgres' password='111' host='localhost' port='5432' dbname='postgres'";
        std::stringstream str_query,str_query2;
        str_query2 << "DROP DATABASE " << name << ";";

        str_query << "CREATE DATABASE " << name <<  " ENCODING 'UTF8' TEMPLATE template1;";

        //TEMPLATE template1 - это некий прототип,
        //который будет использован за образец при создании новой БД

        pqxx::connection con(str_local);

        pqxx::nontransaction query2(con, "Sample"); //<--- ключевой момент
        //операция создания базы должна быть "не транкзационной"
        pqxx::result res2 = query2.exec(str_query2.str());

        pqxx::nontransaction query(con, "Sample"); //<--- ключевой момент
        //операция создания базы должна быть "не транкзационной"
        pqxx::result res = query.exec(str_query.str());
    }
    catch(const pqxx::sql_error& e)
    {
        std::cout<<"problem: "<<e.what()<<std::endl;
    }
}


bool Database::init( std::string db, std::string tb ) {
    create_db(db);
    drop_table(tb);
    create_table(tb);
    db_name = db;
    m_table_name = tb;
    return true;
}
