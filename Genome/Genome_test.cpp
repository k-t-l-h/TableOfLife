#include <gtest/gtest.h>
#include "Genome.h"

TEST(TEST_FITNESS, default_value) {
  //приспособленность по дефолту 0
  const std::size_t b_size = 0;
  Genome<b_size> g;
  ASSERT_FLOAT_EQ(g.GetFitness(), 0);
}

TEST(TEST_FITNESS, not_greater_than_one) {
  //максимальная приспособленность 1
  const std::size_t b_size = 0;
  Genome<b_size> g;
  g.SetFitness(2);
  ASSERT_FLOAT_EQ(g.GetFitness(), 1);
}

TEST(TEST_FITNESS, all_good) {
  //между 0 и 1 должно устанавливаться правильно
  const std::size_t b_size = 0;
  Genome<b_size> g;
  float fitness = 0.5;
  g.SetFitness(fitness);
  ASSERT_FLOAT_EQ(g.GetFitness(), fitness);
}

TEST(TEST_GENES, default_value) {
  //дефолтный массив равен по длине максимальному размеру
  const std::size_t b_size = 0;
  Genome<b_size> g(b_size);
  auto v = g.GetGenes();
  ASSERT_EQ(v.size(), b_size);
}

TEST(TEST_GENES, default_value_2) {
  //дефолтное значение гена - 0
  const std::size_t b_size = 1;
  Genome<b_size> g(b_size);
  auto v = g.GetGenes();
  for(size_t i = 0; i < v.size(); i++) {
   ASSERT_EQ(v[i].to_ulong(), 0);
  }
}

TEST(TEST_GENES, test_size) {
  //размер не должен превышать заданный при инициализации
  const std::size_t b_size = 0;
  Genome<b_size> g(b_size);

  std::vector<std::bitset<b_size>> v_set = {std::bitset<b_size>(1)};
  g.SetGenes(v_set);

  auto v_get = g.GetGenes();
  ASSERT_EQ(v_get.size(), b_size);
  ASSERT_NE(v_get.size(), v_set.size());
}

TEST(TEST_GENES, all_good) {
  //хороший пример
  const std::size_t b_size = sizeof(int);
  const std::size_t max = 10;
  Genome<b_size> g(max);

  std::vector<std::bitset<b_size>> v = {};
  for (int i = 0; i < max; ++i) {
    v.push_back(i);
  }
  g.SetGenes(v);

  auto v2 = g.GetGenes();

  for(size_t i =0; i < v2.size() && i < v.size(); i++){
    ASSERT_EQ(v[i], v2[i]);
  }
}

TEST(TEST_GENE, set_correct) {
  //проверка того, что один ген устанавливается правильно
  const std::size_t b_size = sizeof(int);
  const std::size_t max = 1;
  int value = 5;
  Genome<b_size> g(max);
  g.SetGene(0, value);
  auto v = g.GetGenes();
  ASSERT_EQ(static_cast<int>(v[0].to_ulong()), value);
}

TEST(TEST_GENE, get_correct) {
    //проверка того, что один ген возвращается правильно
    const std::size_t b_size = sizeof(int);
    const std::size_t max = 1;
    int value = 5;
    Genome<b_size> g(max);
    g.SetGene(0, value);
    ASSERT_EQ(g.GetGenes(0). value);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
