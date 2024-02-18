#include <gtest/gtest.h>
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
  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

TEST_F(FibHeapTest, Empty) {
    EXPECT_TRUE(h_.empty());
}

int main() {
    //adding new code
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}