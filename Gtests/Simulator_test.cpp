#include <gtest/gtest.h>
#include "../Simulator/Simulator.h"

//по дефолту функция приспособленности выставляет 0
  TEST(TEST_SELECTION, test_constructor_simulate){
  const std::size_t N = sizeof(int);
  float fitness = 1;
  Simulator<N> sm;
  Genome<N> g;
  g.SetFitness(fitness);
  sm.Simulate(&g);
  ASSERT_FLOAT_EQ(g.GetFitness(), 0);
  ASSERT_FLOAT_NE(g.GetFitness(), fitness);
 }

 //по дефолту функция окончания выставляет true
 TEST(TEST_SELECTION, test_constructor_exit){
  const std::size_t N = sizeof(int);
  float fitness = 1;
  Simulator<N> sm;
  Genome<N> g;
  ASSERT_EQ(sm.Exit(&g), true);
 }

 //функция выставляется правильно и возвращает правильно
TEST(TEST_SELECTION, test_set_up_simulate){
  const std::size_t N = sizeof(int);
  Simulator<N> sm;
  Genome<N> g;
  //сетап функции возврающей false
  sm.SetExit([](Genome<N>*){return false;});
  //проверка того, что теперь вернется false
  ASSERT_EQ(sm.Exit(&g), false);
}


//функция 2 тоже выставляется правильно
TEST(TEST_SELECTION, test_set_up_exit){
  const std::size_t N = sizeof(int);
  float fitness = 1;
  Simulator<N> sm;
  Genome<N> g;
  //сетап функции возврающей false
  sm.SetRule([](Genome<N>* g){g->SetFitness(fitness);});
  //проверка того, что теперь вернется false
  ASSERT_FLOAT_EQ(g.GetFitness(), fitness);
}


//проверить, что при подаче null функция не заменяется
TEST(TEST_SELECTION, test_set_up_simulate_null){
  const std::size_t N = sizeof(int);
  Simulator<N> sm;
  Genome<N> g;
  sm.SetRule(nullptr);
  ASSERT_NO_THROW(sm.Simulate(&g));

}

//при подаче null функция не заменяется
TEST(TEST_SELECTION, test_set_up_exit_null) {
  const std::size_t N = sizeof(int);
  Simulator<N> sm;
  Genome<N> g;
  sm.SetExit(nullptr);
  ASSERT_NO_THROW(sm.Simulate(&g));
}


//с nullptr функция остановки выдает false
TEST(TEST_SELECTION, test_set_up_exit_null) {
  const std::size_t N = sizeof(int);
  Simulator<N> sm;
  ASSERT_EQ(sm.Exit(nullptr), false);
}

