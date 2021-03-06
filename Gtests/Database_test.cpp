#include <gtest/gtest.h>
#include "../IDatabase/Database.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid.hpp>
#include "../Result/Result.h"
#include <vector>


//db connects ok
TEST(TEST_CONNECTION, connection_on){
    Database db;
    ASSERT_EQ(db.connect(),true);
}

//db create table works
TEST(TEST_INSERT, create_table_ok){
    Database db;
    if (db.connect()){
        ASSERT_EQ( db.init("solution", "testsolution"), true );
    } else {
        ASSERT_EQ(true, false);
    }
}


//db insert query
TEST(TEST_INSERT, insert_ok){
     Database db;
     if (db.connect()){
         u::uuid u1 = boost::uuids::random_generator()();
         std::vector<size_t> vec = {0,0,1,1,1,0};
         std::vector<Classes> cls= {{"Algo","Krimov", 2},{"C++","Juliana", 3}};
         Result res = {u1, vec, cls, cls.size()};
         ASSERT_EQ(db.Insert(res), true);
     } else {
         ASSERT_EQ(true, false);
     }
}



//db select query
TEST(TEST_INSERT, select_ok){
    Database db;
    if (db.connect()){
        u::uuid u1 = boost::uuids::random_generator()();
        std::vector<size_t> vec = {0,0,1,1,1,0};
        std::vector<Classes> cls= {{"Algo","Krimov", 2},{"OS","Linus", 3}};
        Result res = {u1, vec, cls, cls.size()};
        ASSERT_EQ(db.Insert(res), true);

        Result res_cmp = db.Select(u1);

        EXPECT_EQ(res_cmp.result, vec);
        EXPECT_EQ(res_cmp.ClassesNumber, 2);
        EXPECT_EQ(res_cmp.classes[0].id_groups, 2);
        EXPECT_EQ(res_cmp.classes[1].id_groups, 3);
        EXPECT_EQ(true, res_cmp.classes[1].teacher == "Linus");
        EXPECT_EQ(true, res_cmp.classes[0].teacher == "Krimov");


    } else {
        ASSERT_EQ(true, false);
    }
}


TEST(TEST_INSERT, select_not_ok){
    Database db;
    if (db.connect()){
        u::uuid u1 = boost::uuids::random_generator()();

        Result res_cmp = db.Select(u1);

        EXPECT_EQ(res_cmp.result.size(), 0);
    } else {
        ASSERT_EQ(true, false);
    }
}


TEST( TEST_CREATE_DROP, must_work ){
    auto test_name = "db_name";
    Database db;
}