#include <gtest/gtest.h>

#include "../Creator/RandomCreator.h"
#include "../Creator/SimpleCreator.h"

TEST(TEST_CREATOR, size_test) {
  //создает нужное количество особей
  const std::size_t N = sizeof(int);
  std::size_t check = 5;
  SimpleCreator<N> sc;
  auto v = sc.Create(check, check, check);
  ASSERT_EQ(v.size(), check);
}

TEST(TEST_CREATOR, nullptr_check) {
  //особи не пустые
  const std::size_t N = sizeof(int);
  std::size_t check = 10;
  SimpleCreator<N> sc;
  auto v = sc.Create(check, check, check);
  for (size_t i = 0; i < check; i++) {
    ASSERT_NE(v[i], nullptr);
  }
}

TEST(TEST_CREATOR, diff_test) {
  //создает различных особей
  const std::size_t N = sizeof(int);
  std::size_t check = 2;
  SimpleCreator<N> sc;
  auto v = sc.Create(check, check, check);
  //два предмета по порядку
  ASSERT_EQ(v.size(), check);
  //не должны совпадать
  ASSERT_NE(v[0]->GetGene(0),v[1]->GetGene(0));
}

TEST(TEST_RANDOM_CREATOR, size_test_r) {
  //создает нужное количество особей
  const std::size_t N = sizeof(int);
  std::size_t check = 5;
  RandomCreator<N> rc;
  auto v = rc.Create(check, check, check);
  ASSERT_EQ(v.size(), check);
}

TEST(TEST_RANDOM_CREATOR, nullptr_check_r) {
  //особи не пустые
  const std::size_t N = sizeof(int);
  std::size_t check = 10;
  RandomCreator<N> rc;
  auto v = rc.Create(check, check, check);
  for (size_t i = 0; i < check; i++) {
    ASSERT_NE(v[i], nullptr);
  }
}

TEST(TEST_RANDOM_CREATOR, size_test_neg_r) {
  //создает нулевое количество особей в случае чего
  const std::size_t N = sizeof(int);
  std::size_t check = -1;
  RandomCreator<N> rc;
  auto v = rc.Create(check, check, check);
  ASSERT_EQ(v.size(), 0);
}

