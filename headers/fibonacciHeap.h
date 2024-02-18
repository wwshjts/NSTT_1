#include <vector>
#include <list>

class Node {
    int degree_;

public:
    int val;
    std::vector<Node> successors;

    Node(int val) {
        this->val = val; 
        this->degree_ = 0;
    }

    void addChild(Node s) {
        successors.push_back(s);
        degree_++;
    }

    int degree() {
        return degree_;
    }
};

class FibHeap {

    Node* min_node_;
    void consolidate(FibHeap fib);

public:
    // constructors
    FibHeap() {
        min_node_ = nullptr;
    } 

    FibHeap(std::vector<int> vec);

    void insert(int val);
    int peek_min();
    int empty();
    int extract_min();
    void decrease_key(int s, int k);
    static void merge(FibHeap* dst, FibHeap* src); 

    std::list<Node*> roots;
};
