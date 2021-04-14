#include <gtest/gtest.h>
#include "Builder.h"

//по дефолту создается ГА
TEST(TEST_BUILDER, create) {
  const std::size_t N = sizeof(int);
  Builder<N> builder;
  auto result = builder.GetResut();
  ASSERT_NE(result, nullptr);
}

//создается новый ГА
TEST(TEST_BUILDER, reset_test) {
  const std::size_t N = sizeof(int);
  Builder<N> builder;
  auto result = builder.GetResut();
  builder.Reset();
  auto result2 = builder.GetResult();
  ASSERT_NE(result, result2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}