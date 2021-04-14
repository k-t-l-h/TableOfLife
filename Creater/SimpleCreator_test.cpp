#include <gtest/gtest.h>
#include "SimpleCreator.h"

TEST(TEST_CREATOR, size_test) {
  //создает нужное количество особей
  const std::size_t N = sizeof(int);
  std::size_t check = 5;
  SimpleCreator<N> sc;
  auto v = sc.Create(check, check);
  ASSERT_EQ(v.size(), check);
}

TEST(TEST_CREATOR, nullptr_check) {
  //особи не пустые
  const std::size_t N = sizeof(int);
  std::size_t check = 10;
  SimpleCreator<N> sc;
  auto v = sc.Create(check, check);
  for (size_t i = 0; i < check; i++) {
    ASSERT_NE(v[i], nullptr);
  }
}

TEST(TEST_CREATOR, size_test_neg) {
  //создает нулевое количество особей в случае чего
  const std::size_t N = sizeof(int);
  std::size_t check = -1;
  SimpleCreator<N> sc;
  auto v = sc.Create(check, check);
  ASSERT_EQ(v.size(), 0);
}


TEST(TEST_CREATOR, diff_test) {
  //создает различных особей
  const std::size_t N = sizeof(int);
  std::size_t check = 2;
  SimpleCreator<N> sc;
  auto v = sc.Create(check, check);
  //два предмета по порядку
  ASSERT_EQ(v.size(), check);
  //не должны совпадать
  ASSERT_NE(v[0]->GetGene(0),v[1]->GetGene(0));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}