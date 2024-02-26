#include <vector>
#include <list>
class Node;

struct listNode {
    struct listNode* next;
    struct listNode* prev;
    Node* node;

    listNode() { 
        next = nullptr;
        prev = nullptr;
        node = nullptr;
    }
};

class LinkedList {
    listNode* head_;
    listNode* tail_;
    size_t size_;

public:
    LinkedList() {
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }
    ~LinkedList();
    int empty();
    size_t const size();
    void add(Node*);
    Node* peek();
    Node* pop();
    void remove(Node*);
    void merge(LinkedList*);
    int equal(LinkedList*);
};

// TODO maybe this class must be inner class of FibHeap? 
class Node {
public:
    int val;
    // this things must be protected somehow
    int is_labeled;
    Node* parent;
    listNode* link;
    std::list<Node*> successors;

    Node(int val) {
        this->val = val; 
        is_labeled = 0;
        parent = nullptr;
    }

    void addChild(Node* s) {
        successors.push_back(s);
        s->parent = this;
    }

    int degree() {
        return successors.size();
    }
};

class FibHeap {

    Node* min_node_;
    size_t n_;
    void consolidate();
    void addRoot(Node* v);
    void DFS_delete(Node* v);

public:
    // constructors
    FibHeap() {
        min_node_ = nullptr;
        n_ = 0;
    } 

    FibHeap(std::vector<int> data);
    ~FibHeap();
    // insert val into heap, returns ptr on it
    Node* insert(int val);
    int peek_min();
    // return minimum of val and heap.peek_min() if heap is empty returns val
    int or_peek_min(int val);
    int empty();
    size_t d();
    int extract_min();
    void decrease_key(Node* s, int k);
    void merge(FibHeap* src); 
    void put_away(Node* s);

    std::list<Node*> roots;
};
