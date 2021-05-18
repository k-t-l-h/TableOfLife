#include <gtest/gtest.h>
#include "../IDatabase/Database.h"


TEST(TEST_CONNECTION, connection_on){
    Database db;
    ASSERT_EQ(db.connect(),false);
}

