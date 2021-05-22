#include <gtest/gtest.h>
#include "../IDatabase/Database.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid.hpp>


//db connects ok
TEST(TEST_CONNECTION, connection_on){
    Database db;
    ASSERT_EQ(db.connect(),true);
}


//db create table works
TEST(TEST_INSERT, create_table_ok){
    Database db;
    auto table_name = "testSolution";
    if (db.connect()){
        db.drop_table(table_name);
        db.create_tables(table_name);
        db.drop_table(table_name);
    } else {
        ASSERT_EQ(true, false);
    }

}


//db insert query
TEST(TEST_INSERT, insert_ok){
     Database db;
     if (db.connect()){
         db.create_tables("testSolution");
         u::uuid u1 = boost::uuids::random_generator()();
         std::vector<size_t> vec = {0,0,1,1,1,0};
         Result res = {u1, vec};
         ASSERT_EQ(db.Insert(res), true);
         db.drop_table("testSolution");
     } else {
         ASSERT_EQ(true, false);
     }
}



//db select query
TEST(TEST_INSERT, select_ok){
    Database db;
    if (db.connect()){
        db.create_tables("testSolution");
        u::uuid u1 = boost::uuids::random_generator()();
        std::vector<size_t> vec = {0,0,1,1,1,0};
        Result res = {u1, vec};
        ASSERT_EQ(db.Insert(res), true);

        Result res_cmp = db.Select(u1);

        EXPECT_EQ(res_cmp.result, vec);
        db.drop_table("testSolution");
    } else {
        ASSERT_EQ(true, false);
    }
}

