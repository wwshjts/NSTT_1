#include <vector>
#include <list>

class Node {
public:
    int val;
    std::vector<Node*> successors;

    Node(int val) {
        this->val = val; 
    }

    void addChild(Node* s) {
        successors.push_back(s);
    }

    int degree() {
        return successors.size();
    }
};

class FibHeap {

    Node* min_node_;
    size_t n_;
    void consolidate();
    void addNode(Node* v);

public:
    // constructors
    FibHeap() {
        min_node_ = nullptr;
        n_ = 0;
    } 

    FibHeap(std::vector<int> data);

    void insert(int val);
    int peek_min();
    int empty();
    size_t d();
    int extract_min();
    void decrease_key(int s, int k);
    void merge(FibHeap* src); 

    std::list<Node*> roots;
};
