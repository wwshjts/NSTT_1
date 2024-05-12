#include <gtest/gtest.h>
#include <vector>
#include <set>
#include "../sources/fibonacciHeap.h"

FibHeap<char> get_alphabet(){
    FibHeap<char> res;
    for (char ch = 'a'; ch <= 'z'; ch++) {
        res.insert(ch);
    }
    return res;
}

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

TEST(fib_heap_test, move) {
    FibHeap<char> alph = get_alphabet();

    for (char ch = 'a'; ch <= 'z'; ch++) {
        EXPECT_EQ(ch, alph.extract_min());
    }
    alph.empty();
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

TEST(fib_heap_test, decrease_key) {
    FibHeap<std::string> string_heap;

    string_heap.insert("b");
    string_heap.insert("aaa");    
    FibHeapNode<std::string>* s = string_heap.insert_node("c");
    string_heap.decrease_key(s, "a");
    EXPECT_EQ("a", string_heap.extract_min());
    EXPECT_EQ("aaa", string_heap.extract_min());
}


TEST(fib_heap_test, stress_test) {
    FibHeap<int> heap;

    for (size_t i = 10000; i > 0; i--) {
        heap.insert(i);
    }

    for (size_t i = 1; i <= 10000; i++) {
        EXPECT_EQ(i, heap.extract_min());
    }
}

TEST(fib_heap_test, basic_iterator_test) {
    FibHeap<std::string> heap;
    std::set<std::string> expected;
    std::set<std::string> actual;


    for (size_t i = 10; i > 0; i--) {
        heap.insert(std::to_string(i));
        expected.insert(std::to_string(i));
    }

    for (std::string s : heap) {
        actual.insert(s);   
    }

    EXPECT_EQ(actual, expected);

}

TEST(fib_heap_test, iterator_test) {
    FibHeap<std::string> heap;
    std::set<std::string> expected;
    std::set<std::string> actual;


    for (size_t i = 10; i > 0; i--) {
        heap.insert(std::to_string(i));
        expected.insert(std::to_string(i));
    }

    heap.consolidate();

    for (std::string s : heap) {
        actual.insert(s);   
    }

    EXPECT_EQ(actual, expected);

}

TEST(fib_heap_test, empty_iterator_test) {
    FibHeap<std::string> heap;
    std::set<std::string> actual;

    for (std::string s : heap) {
        actual.insert(s);   
    }
}

int main() {
    //adding new code
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
