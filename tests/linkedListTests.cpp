#include <gtest/gtest.h>
#include <vector>
#include "../sources/fibonacciHeap.h"

class LinkedListTest : public testing::Test {
 protected:
    LinkedListTest() {
        std::vector<int> tmp = {1, 2, 3, 4, 5};
        for (int item : tmp) {
            a.push_back(new Node(item));
        }
    }

    ~LinkedListTest() {
        for (Node* item : a) {
            delete(item);
        }

    }

public:
    void initList(LinkedList* s, std::vector<Node*>& vec) {
        for (Node* item : vec) {
            s->add(item);
        }
    }
    std::vector<Node*> a;
};

TEST_F(LinkedListTest, Empty) {
    LinkedList l1;
    LinkedList l2;
    EXPECT_TRUE(l1.equal(l1));
    EXPECT_TRUE(l2.equal(l2));
}

TEST_F(LinkedListTest, Equal) {
    LinkedList list;
    LinkedList other; 
    for (Node* v : a) {
        list.add(v);
        other.add(v);
    }
    EXPECT_TRUE(list.equal(other));
    EXPECT_TRUE(other.equal(list));
    
}

TEST_F(LinkedListTest, Get) {
    LinkedList list;
    initList(&list, a);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(5, list.pop()->val);
    EXPECT_EQ(4, list.pop()->val);
    EXPECT_EQ(3, list.pop()->val);
    EXPECT_EQ(2, list.pop()->val);
    EXPECT_EQ(1, list.pop()->val);
    EXPECT_TRUE(list.empty());
}

TEST_F(LinkedListTest, RemoveOneNode) {
    LinkedList list;
    initList(&list, a);

    list.remove(a[3]); 
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(4, list.size());
    EXPECT_EQ(5, list.pop()->val);
    EXPECT_EQ(3, list.pop()->val);
    EXPECT_EQ(2, list.pop()->val);
    EXPECT_EQ(1, list.pop()->val);
}

TEST_F(LinkedListTest, RemoveSomeNodes) {
    LinkedList list;
    initList(&list, a);
    list.remove(a[3]); 
    list.remove(a[1]); 
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(3, list.size());
    EXPECT_EQ(5, list.pop()->val);
    EXPECT_EQ(3, list.pop()->val);
    EXPECT_EQ(1, list.pop()->val);
}

TEST_F(LinkedListTest, RemoveAllNodes) {
    LinkedList list;
    initList(&list, a);
    for (Node* v : a) {
        list.remove(v);
    }
    EXPECT_EQ(0, list.size());
    EXPECT_TRUE(list.empty());
}

// TODO Broken merge?
/*
TEST_F(LinkedListTest, MergeEmptyEmpty) {
    LinkedList l1;
    LinkedList l2;

    l1.merge(&l2);
    EXPECT_EQ(0, l1.size());
    EXPECT_TRUE(l1.empty());
}

TEST_F(LinkedListTest, MergeFullEmpty) {
    LinkedList list;
    initList(&list, a);
    size_t res = list.size();
    LinkedList l;

    list.merge(&l);
    EXPECT_EQ(res, list.size());
    EXPECT_FALSE(list.empty());
}

TEST_F(LinkedListTest, MergeEmptyFull) {
    LinkedList list;
    initList(&list, a);
    size_t res = list.size();
    LinkedList l = LinkedList();

    l.merge(&list);
    EXPECT_EQ(res, l.size());
    EXPECT_FALSE(l.empty());
    EXPECT_TRUE(l.equal(&list));
}

TEST_F(LinkedListTest, Merge) {
    LinkedList l1;
    LinkedList l2;
    l1.add(new Node{1}); 
    l1.add(new Node{2}); 
    l2.add(new Node{3}); 
    l2.add(new Node{4}); 

    l1.merge(&l2);
    EXPECT_EQ(4, l1.size());
    EXPECT_EQ(4, l1.peek()->val);
    delete(l1.pop());
    EXPECT_EQ(3, l1.peek()->val);
    delete(l1.pop());
    EXPECT_EQ(2, l1.peek()->val);
    delete(l1.pop());
    EXPECT_EQ(1, l1.peek()->val);
    delete(l1.pop());
    EXPECT_TRUE(l1.empty());
}
*/
int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}