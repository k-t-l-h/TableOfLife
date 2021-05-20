#include <gtest/gtest.h>
#include "../GenAlgo/GA.h"

TEST(TEST_GA, test_ok_run) {
    const std::size_t N = sizeof(int);
    GenAlgo<N> genAlgo(0, 0, 0, 5);
    ASSERT_NO_THROW(genAlgo.Run());
}

//до прогона не должно быть результата
TEST(TEST_GA, test_empty) {
    const std::size_t N = sizeof(int);
    GenAlgo<N> genAlgo(0,0,0, 0);
    auto result = genAlgo.GetBest();
    ASSERT_EQ(result.size(), 0);
}


//после прогона результат должен быть
TEST(TEST_GA, test_not_empty) {
    const std::size_t N = sizeof(int);
    GenAlgo<N> genAlgo(0,0,0, 0);
    genAlgo.Run();
    auto result = genAlgo.GetBest();
    ASSERT_NE(result.size(), 0);
    ASSERT_EQ(result.size(), 1);
}

//тут были тесты приватного метода через friend class, но мы их убрали