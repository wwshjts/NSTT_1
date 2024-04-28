#include <gtest/gtest.h>
#include <vector>
#include "../sources/fibonacciHeap.h"

// class FibHeapTest : public testing::Test {
//  protected:
//     FibHeap h_;
//     std::vector<int> v = {1, 2, -42};
// };
TEST(fibnode_test, string_test) {
    FibHeapNode<std::string> greeting { "hello" };
    EXPECT_EQ("hello", *greeting);
}

TEST(fibnode_test, vector_test) {
    std::vector<int> vec = {1, 2, 3, 4};
    FibHeapNode<std::vector<int>> node { vec };
    EXPECT_EQ(4, node->size());
}

TEST(fibnode_test, add_child) {
    FibHeapNode<int> n1 { 1 };    
    FibHeapNode<int> n2 { 2 };
    n1.add_child(&n2);

}

TEST(list_test, add_remove) {
    list<int> l;
    FibHeapNode<int> node { 42 };
    l.add(&node);
    l.remove(&node);
    EXPECT_TRUE(l.empty());
}

TEST(list_test, splice) {
    list<int> l1;
    list<int> l2;

    FibHeapNode<int> n1 { 1 };    
    FibHeapNode<int> n2 { 2 };
    FibHeapNode<int> n3 { 3 };

    l1.add(&n1);
    l1.add(&n3);
    l2.add(&n2);

    l1.remove(&n3);

    l1.splice(l2);
    EXPECT_EQ(2, l1.size());
    EXPECT_TRUE(l2.empty());
}

TEST(fib_heap_test, init) {
    FibHeap<std::string> string_heap;
    string_heap.insert("b");
    string_heap.insert("a");
    EXPECT_EQ("a", string_heap.peek_min());
}

// TEST(fib_heap_test, extract_min) {
//     FibHeap<int> string_heap;
//     string_heap.insert(1);
//     string_heap.insert(2);
//     string_heap.insert(3);
//     string_heap.insert(4);
//     string_heap.insert(5);

//     EXPECT_EQ(1, string_heap.extract_min());
// }

TEST(fib_heap_test, extract_min) {
    FibHeap<std::string> string_heap;
    string_heap.insert("b");
    string_heap.insert("a");
    string_heap.insert("aaa");
    string_heap.insert("abbc");
    string_heap.insert("abbb");

    EXPECT_EQ("a", string_heap.extract_min());
    EXPECT_EQ("aaa", string_heap.extract_min());
    EXPECT_EQ("abbb", string_heap.extract_min());
    EXPECT_EQ("abbc", string_heap.extract_min());
    EXPECT_EQ("b", string_heap.extract_min());
}

// TEST_F(FibHeapTest, InitWithVector) {
//     FibHeap tmp{v};
//     EXPECT_EQ(-42, tmp.peek_min());
// }

// TEST_F (FibHeapTest, PeekMin) {
//     h_.insert(0);
//     h_.insert(1);
//     h_.insert(-11);
//     h_.insert(42);
//     EXPECT_EQ(-11, h_.peek_min());
// }

// TEST_F (FibHeapTest, Empty) {
//     EXPECT_TRUE(h_.empty());
//     h_.insert(1);
//     EXPECT_FALSE(h_.empty());
// }

// TEST_F (FibHeapTest, Merge) {
//     h_.insert(0);
//     h_.insert(1);
//     FibHeap tmp{v};
//     h_.merge(tmp);
//     EXPECT_EQ(-42, h_.peek_min());
// }

// TEST_F (FibHeapTest, MergeNonEmptyAndEmpty) {
//     h_.insert(0);
//     h_.insert(1);
//     FibHeap tmp;
//     h_.merge(tmp);
//     EXPECT_EQ(0, h_.peek_min());
// }

// TEST_F (FibHeapTest, MergeEmpty) {
//     FibHeap tmp;
//     h_.merge(tmp);
//     EXPECT_TRUE(h_.empty());
// }

// TEST_F (FibHeapTest, ExtractMin) {
//     FibHeap tmp{v};
//     EXPECT_EQ(-42, tmp.extract_min());
//     EXPECT_EQ(1, tmp.extract_min());
//     EXPECT_EQ(2, tmp.extract_min());
//     EXPECT_TRUE(tmp.empty());
// }

// TEST_F (FibHeapTest, DecreaseKey) {
//     Node* v = h_.insert(10);
//     h_.insert(0);
//     h_.insert(3);
//     h_.insert(-2);
//     h_.decrease_key(v, -42);
//     EXPECT_EQ(-42, h_.extract_min());
//     EXPECT_EQ(-2, h_.extract_min());
//     EXPECT_EQ(0, h_.extract_min());
//     EXPECT_EQ(3, h_.extract_min());
//     EXPECT_TRUE(h_.empty());
// }

// TEST_F (FibHeapTest, ConsolidateTest) {
//     FibHeap heap;
//     for (int i = 0; i < 10000; i++) {
//         heap.insert(i);
//     }
//     for (int i = 0; i < 10000; i++) {
//         EXPECT_EQ(i, heap.extract_min());
//     }

// }

// TEST_F (FibHeapTest, CopyCtrTest) {
//     for (int i = 0; i < 10; i++) {
//         h_.insert(i);
//     }
//     FibHeap h1 = h_;
//     EXPECT_EQ(h1.size(), h_.size()); 
//     while (!h_.empty()) {
//         EXPECT_EQ(h_.extract_min(), h1.extract_min());
//     }
// }

// TEST_F (FibHeapTest, AssignmentOperatorTest) {
//     for (int i = 0; i < 10; i++) {
//         h_.insert(i);
//     }
//     FibHeap h1;
//     h1 = h_;
//     EXPECT_EQ(h1.size(), h_.size()); 
//     while (!h_.empty()) {
//         EXPECT_EQ(h_.extract_min(), h1.extract_min());
//     }
// } 


int main() {
    //adding new code
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
