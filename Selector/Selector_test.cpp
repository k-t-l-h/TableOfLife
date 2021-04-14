#include <gtest/gtest.h>
#include "Creater/SimpleCreator.h"
#include "Selector/Selector.h"

//при передаче nullptr не должно быть ошибок
TEST(TEST_SELECTION, nullptr_test){
  const std::size_t N = sizeof(int);
  const std::size_t max = 2;

  Selector<N> s;
  SimpleCreator<N> sc;
  ASSERT_NO_THROW(s.Select(nullptr));
}

//при передаче пустого вектора не должно быть ошибок
TEST(TEST_SELECTION, empty_test){
  const std::size_t N = sizeof(int);
  const std::size_t max = 0;

  Selector<N> s;
  SimpleCreator<N> sc;
  auto v = sc.Create(max, max);
  ASSERT_NO_THROW(s.Select(&v));
}

//при передаче пустого вектора не должно быть ошибок
TEST(TEST_SELECTION, empty_test_2){
  const std::size_t N = sizeof(int);
  const std::size_t max = 0;

  Selector<N> s;
  SimpleCreator<N> sc;
  auto v = sc.Create(max, max);
  auto g = s.Select(&v);
  ASSERT_EQ(g, nullptr);

}

//при передаче вектора из одного элемента должен возвращаться этот
//элемент и вектор должен быть пуст
TEST(TEST_SELECTION, one_test){
  const std::size_t N = sizeof(int);
  const std::size_t max = 1;

  Selector<N> s;
  SimpleCreator<N> sc;
  auto v = sc.Create(max, max);
  auto eq = v[0];
  auto g = s.Select(&v);
  ASSERT_EQ(g, eq);
  ASSERT_EQ(v.size(), 0);

}

//при передаче вектора из нескольких элементов
//должен возвращаться один элемент с максимальной приспособленностью
TEST(TEST_SELECTION, all_test){
  const std::size_t N = sizeof(int);
  const std::size_t max = 2;

  Selector<N> s;
  SimpleCreator<N> sc;
  auto v = sc.Create(max, max);
  auto eq = v[1];
  v[1]->SetFitness(1);
  auto g = s.Select(&v);
  ASSERT_EQ(g, eq);
  ASSERT_EQ(v.size(), 1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}