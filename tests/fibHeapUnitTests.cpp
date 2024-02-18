#include <gtest/gtest.h>
#include <vector>
#include "../headers/fibonacciHeap.h"

class FibHeapTest : public testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:
/*
  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }
*/

    FibHeap h_;
    std::vector<int> v = {1, 2, -42};
  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

TEST_F(FibHeapTest, InitWithVector) {
    FibHeap tmp{v};
    EXPECT_EQ(-42, tmp.peek_min());
}

TEST_F (FibHeapTest, PeekMin) {
    h_.insert(0);
    h_.insert(1);
    h_.insert(-11);
    h_.insert(42);
    EXPECT_EQ(-11, h_.peek_min());
}

TEST_F (FibHeapTest, Empty) {
    EXPECT_TRUE(h_.empty());
    h_.insert(1);
    EXPECT_FALSE(h_.empty());
}

TEST_F (FibHeapTest, Merge) {
    h_.insert(0);
    h_.insert(1);
    FibHeap tmp{v};
    h_.merge(&tmp);
    EXPECT_EQ(-42, h_.peek_min());
}

TEST_F (FibHeapTest, MergeNonEmptyAndEmpty) {
    h_.insert(0);
    h_.insert(1);
    FibHeap tmp;
    h_.merge(&tmp);
    EXPECT_EQ(0, h_.peek_min());
}

TEST_F (FibHeapTest, MergeEmpty) {
    FibHeap tmp;
    h_.merge(&tmp);
    EXPECT_TRUE(h_.empty());
}

TEST_F (FibHeapTest, ExtractMin) {
    FibHeap tmp{v};
    EXPECT_EQ(-42, tmp.extract_min());
    EXPECT_EQ(1, tmp.extract_min());
    EXPECT_EQ(2, tmp.extract_min());
    EXPECT_TRUE(tmp.empty());
}

TEST_F (FibHeapTest, DecreaseKey) {
    Node* v = h_.insert(10);
    h_.insert(0);
    h_.insert(3);
    h_.insert(-2);
    h_.decrease_key(v, -42);
    EXPECT_EQ(-42, h_.extract_min());
    EXPECT_EQ(-2, h_.extract_min());
    EXPECT_EQ(0, h_.extract_min());
    EXPECT_EQ(3, h_.extract_min());
    EXPECT_TRUE(h_.empty());
}

int main() {
    //adding new code
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}