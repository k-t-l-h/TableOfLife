#include <gtest/gtest.h>
#include <typeinfo>


#include "../Creator/RandomCreator.h"
#include "../Creator/SimpleCreator.h"
#include "../GABuilder/Builder.h"

#include "../Mutator/ReverseMutator.h"
#include "../Mutator/SimpleMutator.h"

#include "../Mater/SimpleMater.h"
#include "../Mater/TwoDotsMater.h"

#include "../Selector/Selector.h"
#include "../Selector/TopSelector.h"

#include "../Simulator/Simulator.h"
//по дефолту создается ГА

TEST(TEST_BUILDER, create) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    auto result = builder.GetResult();
    ASSERT_NE(result, nullptr);
}

//создается новый ГА
TEST(TEST_BUILDER, reset_test) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    auto result = builder.GetResult();
    builder.Reset(0, 0);
    auto result2 = builder.GetResult();
    ASSERT_NE(result, result2);
}

//по дефолту устанавливается nullptr
TEST(TEST_BUILDER, set_up_default) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    auto res = builder.GetResult();
    ASSERT_EQ(res->Mater, nullptr);
}

TEST(TEST_BUILDER, set_up_creator) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    builder.SetCreator();
    SimpleCreator<N> m;
    auto res = builder.GetResult();
    ASSERT_NE(res->Creator, nullptr);
    ASSERT_EQ(typeid(*(res->Creator)) == typeid(m), true);
}

TEST(TEST_BUILDER, set_up_random_creator) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    builder.SetCreator();
    RandomCreator<N> m;
    auto res = builder.GetResult();
    ASSERT_NE(res->Creator, nullptr);
    ASSERT_EQ(typeid(*(res->Creator)) == typeid(m), true);
}


TEST(TEST_BUILDER, set_up_mutator_default) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    auto res = builder.GetResult();
    ASSERT_EQ(res->Mutator, nullptr);
}


TEST(TEST_BUILDER, set_up_mutator) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    builder.SetMutator(1);
    SimpleMutator<N> m(0, 5);
    auto res = builder.GetResult();
    ASSERT_NE(res->Mutator, nullptr);
    ASSERT_EQ(typeid(*(res->Mutator)) == typeid(m), true);
}

TEST(TEST_BUILDER, set_up_reverse_mutator) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    builder.SetReverseMutator(1);
    ReverseMutator<N> m(0, 0);
    auto res = builder.GetResult();
    ASSERT_NE(res->Mutator, nullptr);
    ASSERT_EQ(typeid(*(res->Mutator)) == typeid(m), true);
}


TEST(TEST_BUILDER, set_up_mater_default) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    auto res = builder.GetResult();
    ASSERT_EQ(res->Mater, nullptr);
}

TEST(TEST_BUILDER, set_up_mater) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    builder.SetMater(1);
    Mater<N> m(0);
    auto res = builder.GetResult();
    ASSERT_NE(res->Mutator, nullptr);
    ASSERT_EQ(typeid(*(res->Mutator)) == typeid(m), true);
}

TEST(TEST_BUILDER, set_up_mater_2) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    builder.Set2PointsMater(1);
    TwoPointsMater<N> m(0);
    auto res = builder.GetResult();
    ASSERT_NE(res->Mutator, nullptr);
    ASSERT_EQ(typeid(*(res->Mutator)) == typeid(m), true);
}

TEST(TEST_BUILDER, set_up_select_default) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    auto res = builder.GetResult();
    ASSERT_EQ(res->Selector, nullptr);
}

TEST(TEST_BUILDER, set_up_select) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    builder.SetSelection();
    Selector<N> m;
    auto res = builder.GetResult();
    ASSERT_NE(res->Selector, nullptr);
    ASSERT_EQ(typeid(*(res->Selector)) == typeid(m), true);
}

TEST(TEST_BUILDER, set_up_top_select) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    builder.SetTopSelection();
    TopSelector<N> m;
    auto res = builder.GetResult();
    ASSERT_NE(res->Selector, nullptr);
    ASSERT_EQ(typeid(*(res->Selector)) == typeid(m), true);
}

TEST(TEST_BUILDER, set_up_sim_default) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    auto res = builder.GetResult();
    ASSERT_EQ(res->Simulator, nullptr);
}


TEST(TEST_BUILDER, set_up_sim) {
    const std::size_t N = sizeof(int);
    Builder<N> builder;
    Simulator<N> sm;
    builder.SetSimulator();
    auto res = builder.GetResult();
    ASSERT_NE(res->Simulator, nullptr);
    ASSERT_EQ(typeid(*(res->Simulator)) == typeid(sm), true);
}

