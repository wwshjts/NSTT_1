#include <vector>
#include <list>
#include <set>

class Node;

struct ListNode {
    struct ListNode* next;
    struct ListNode* prev;
    Node* node;

    ListNode() : next(nullptr), prev(nullptr), node(nullptr) {}
    ListNode(Node* node) : next(nullptr), prev(nullptr), node(node) {}
    ~ListNode() = default;
};


class LinkedList {
    friend class FibHeap;
    ListNode* head_;
    ListNode* tail_;
    size_t size_;

public:
    // constructors and destructors
    LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}
    ~LinkedList();

    // returns number of different degrees of the nodes in list
    size_t degree() const;
    void add(Node*);
    void add(ListNode*);
    Node* peek();
    Node* pop();
    void remove(Node*);
    void remove(ListNode*);
    // after merging src is no longer available
    static void merge(LinkedList& dst, LinkedList& src);
    bool equal(LinkedList& other) const;
    bool empty() const;
    size_t size() const;
};

class Node {
    friend class FibHeap;
    friend class LinkedList;

    Node* parent_;
    bool is_labeled_;
    ListNode* link_;
public:
    int val;
    LinkedList successors;

    Node(int val) : val(val), is_labeled_(false), parent_(nullptr), link_(nullptr), successors() {}
    Node(Node& other) : val(other.val), is_labeled_(other.parent_), link_(other.link_), successors(other.successors) {} 
    Node& operator=(Node& other);
    ~Node() = default;

    void addChild(Node* s) {
        successors.add(s);
        s->parent_ = this;
    }

    size_t degree() {
        return successors.size();
    }
};

class FibHeap {

    Node* min_node_;
    size_t n_;
    void addRoot(Node* v);
    void dfs_delete(Node* v);
    void dfs_cpy(ListNode* v);

public:
    LinkedList roots;

    // constructors and destructors
    FibHeap() : min_node_(nullptr), n_(0), roots() {} 
    FibHeap(std::vector<int>& data);
    FibHeap(FibHeap& other);
    FibHeap& operator=(FibHeap& other);
    ~FibHeap();

    // insert val into heap, returns ptr on it
    Node* insert(int val);
    int peek_min();
    // return minimum of val and heap.peek_min() if heap is empty returns val
    int or_peek_min(int val); 
    size_t d() const;
    // return number of different degrees of roots
    size_t degrees() const;
    void consolidate();
    int extract_min();
    void decrease_key(Node* s, int k);
    void merge(FibHeap& src); 
    void put_away(Node* s);
    bool empty() const;
    int size() const {
        return n_;
    }
};
