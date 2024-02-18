#include <vector>
#include <list>

class Node {
    int degree_;

public:
    int val;
    std::vector<Node> successors;

    Node(int val) {
        this->val = val; 
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

    void consolidate(FibHeap fib);
public:
    
    std::list<Node*> roots;

    void insert(int val);
    int peek_min();
    int extract_min();
    void decrease_key(int s, int k);
    void merge(FibHeap* f1, FibHeap* f2); 
};
