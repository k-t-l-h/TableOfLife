#include <gtest/gtest.h>

#include "../Creator/SimpleCreator.h"
#include "../Selector/Selector.h"
#include "../Selector/TopSelector.h"

//при передаче nullptr не должно быть ошибок
TEST(TEST_SELECTION, nullptr_test){
  const std::size_t N = sizeof(int);
  const std::size_t max = 2;

  Selector<N> s;
  ASSERT_NO_THROW(s.Select(nullptr));
}

//при передаче nullptr не должно быть ошибок
  TEST(TEST_SELECTION, nullptr_test_top){
  const std::size_t N = sizeof(int);
  const std::size_t max = 2;

  TopSelector<N> s;
  ASSERT_NO_THROW(s.Select(nullptr));
}

//при передаче пустого вектора не должно быть ошибок
TEST(TEST_SELECTION, empty_test){
  const std::size_t N = sizeof(int);
  const std::size_t max = 0;

  Selector<N> s;
  SimpleCreator<N> sc;
  auto v = sc.Create(max, max, max);
  ASSERT_NO_THROW(s.Select(&v));
}

//при передаче пустого вектора не должно быть ошибок
TEST(TEST_SELECTION, empty_test_top){
  const std::size_t N = sizeof(int);
  const std::size_t max = 0;

  TopSelector<N> ts;
  SimpleCreator<N> sc;
  auto v = sc.Create(max, max, max);
  ASSERT_NO_THROW(ts.Select(&v));
}

//при передаче пустого вектора не должно быть ошибок
TEST(TEST_SELECTION, empty_test_2){
  const std::size_t N = sizeof(int);
  const std::size_t max = 0;

  Selector<N> s;
  SimpleCreator<N> sc;
  auto v = sc.Create(max, max, max);
  auto g = s.Select(&v);
  ASSERT_EQ(g, nullptr);

}

//при передаче пустого вектора не должно быть ошибок
TEST(TEST_SELECTION, empty_test_2_top){
  const std::size_t N = sizeof(int);
  const std::size_t max = 0;

  TopSelector<N> s;
  SimpleCreator<N> sc;
  auto v = sc.Create(max, max, max);
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
  auto v = sc.Create(max, max, max);
  auto eq = v[0];
  auto g = s.Select(&v);
  ASSERT_EQ(g, eq);
  ASSERT_EQ(v.size(), 0);

}

//при передаче вектора из одного элемента должен возвращаться этот
//элемент и вектор должен быть пуст
TEST(TEST_SELECTION, one_test_top){
  const std::size_t N = sizeof(int);
  const std::size_t max = 1;

  TopSelector<N> s;
  SimpleCreator<N> sc;
  auto v = sc.Create(max, max, max);
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
  auto v = sc.Create(max, max, max);
  auto eq = v[1];
  v[1]->SetFitness(1);
  auto g = s.Select(&v);
  ASSERT_EQ(g, eq);
  ASSERT_EQ(v.size(), 1);
}

TEST(TEST_SELECTION, all_test_top){
  const std::size_t N = sizeof(int);
  const std::size_t max = 2;

  TopSelector<N> s;
  SimpleCreator<N> sc;
  auto v = sc.Create(max, max, max);
  auto eq = v[1];
  v[1]->SetFitness(1);
  auto g = s.Select(&v);
  ASSERT_EQ(g, eq);
  ASSERT_EQ(v.size(), 1);
}
