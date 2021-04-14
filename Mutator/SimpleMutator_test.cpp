#include <gtest/gtest.h>
#include "../Mutator/SimpleMutator.h"

//что будет если передать null
TEST(TEST_MUTATOR, zero) {
  const std::size_t N = sizeof(int);
  SimpleMutator<N> sm(0);
  //нет так нет
  ASSERT_NO_THROW(sm.Mutate(nullptr));
  auto answer = sm.Mutate(nullptr);
  ASSERT_EQ(answer, nullptr);

}

TEST(TEST_MUTATOR, zero2) {
  const std::size_t N = sizeof(int);
  float probability = 0;
  //при вероятности мутации в 0 мутации не должно быть
  SimpleMutator<N> sm(probability);

  Genome<N> g(1);
  auto answer = sm.Mutate(&g);
  ASSERT_NE(answer, nullptr);
  ASSERT_EQ(answer.GetGene(0), g.GetGene(0));
}

TEST(TEST_MUTATOR, for_sure) {
  const std::size_t N = sizeof(int);
  float probability = 1;
  //при вероятности мутации в 1 мутация обязана произойти
  SimpleMutator<N> sm(probability);
  Genome<N> g(1);
  //мутация возвращает копию или новый объект
  auto answer = sm.Mutate(&g);
  ASSERT_NE(answer->GetGene(0), g.GetGene(0));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}