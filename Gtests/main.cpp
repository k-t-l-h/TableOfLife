#include <gtest/gtest.h>
//#include "../Gtests/Manager_test.cpp"
#include "Adapter_test.cpp"

TEST(a,aa){
    ASSERT_EQ(1,1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}