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
    h_.merge(tmp);
    EXPECT_EQ(-42, h_.peek_min());
}

TEST_F (FibHeapTest, MergeNonEmptyAndEmpty) {
    h_.insert(0);
    h_.insert(1);
    FibHeap tmp;
    h_.merge(tmp);
    EXPECT_EQ(0, h_.peek_min());
}

TEST_F (FibHeapTest, MergeEmpty) {
    FibHeap tmp;
    h_.merge(tmp);
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
    FibHeap heap;
    for (int i = 0; i < 10000; i++) {
        heap.insert(i);
    }
    for (int i = 0; i < 10000; i++) {
        std::cout << i << std::endl;
        EXPECT_EQ(i, heap.extract_min());
    }

}

TEST_F (FibHeapTest, CopyCtrTest) {
    for (int i = 0; i < 10; i++) {
        h_.insert(i);
    }
    FibHeap h1 = h_;
    EXPECT_EQ(h1.size(), h_.size()); 
    while (!h_.empty()) {
        EXPECT_EQ(h_.extract_min(), h1.extract_min());
    }
}

TEST_F (FibHeapTest, AssignmentOperatorTest) {
    for (int i = 0; i < 10; i++) {
        h_.insert(i);
    }
    FibHeap h1;
    h1 = h_;
    EXPECT_EQ(h1.size(), h_.size()); 
    while (!h_.empty()) {
        EXPECT_EQ(h_.extract_min(), h1.extract_min());
    }
} 


int main() {
    //adding new code
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
