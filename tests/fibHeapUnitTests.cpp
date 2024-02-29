#include <gtest/gtest.h>
#include <vector>
#include "../sources/fibonacciHeap.h"

class FibHeapTest : public testing::Test {
 protected:
    FibHeap h_;
    std::vector<int> v = {1, 2, -42};
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

TEST_F (FibHeapTest, ConsolidateTest) {
    for (int i = 0; i < 100; i++) {
        h_.insert(std::rand());
    }
    h_.consolidate();
    EXPECT_TRUE(h_.degrees() == h_.roots.size());
}


int main() {
    //adding new code
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}