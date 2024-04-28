#include <stdexcept>
#include <vector>
#include <list>
#include <set>
#include <exception>
#include <iostream>

template<typename T>
class list;

// just wrapper for type T
template<typename T>
struct FibHeapNode {
    T value;
    FibHeapNode<T>* parent;
    bool is_labeled = false;

    typename std::list<FibHeapNode<T>*>::iterator link;

    list<T> successors;

    FibHeapNode<T>(const T& val) : value { val } {};
    FibHeapNode<T>(T&& val) : value { std::move(val) } {};

    FibHeapNode<T>& operator=(const FibHeapNode<T>& other) {
        if (this == &other) {
            return this;
        }
        value = other.value;
        is_labeled = other.is_labeled;
        return *this;
    }

    void add_child(FibHeapNode<T>* node) {
        successors.add(node);
    }

    size_t degree() const {
        return successors.size();
    }

    T* operator->() { return &value; }
    T& operator*() { return value; };
    bool operator<(FibHeapNode<T>* other) {
        return value < other->value;
    }
    bool operator<=(FibHeapNode<T>* other) {
        return (value < other->value) || (value == other.value); 
    }
};

template <typename T>
class list {
    std::list<FibHeapNode<T>* > inner_;

public:
    void add(FibHeapNode<T>* node) {
        node->link = inner_.insert(inner_.end(), node);
    }

    // after this field link is invalid
    FibHeapNode<T>* pop() {
        FibHeapNode<T>* res = *(inner_.begin());
        inner_.pop_front();
        return res;
    }

    FibHeapNode<T>* peek() const {
        return *(inner_.end());        
    }

    void remove(FibHeapNode<T>* node) {
        inner_.erase(node->link);
    }

    void splice(list<T>& src) {
        if (&src == this) {
            return;
        }
        inner_.splice(inner_.end(), src.inner_);
    }

    size_t size() const {
        return inner_.size();
    }

    bool empty() const {
        return inner_.empty();
    }

    typename std::list<FibHeapNode<T>*>::iterator begin() {
        return inner_.begin();
    }

    typename std::list<FibHeapNode<T>*>::iterator end() {
        return inner_.end();
    }
};


// class Node;

// struct ListNode {
//     struct ListNode* next;
//     struct ListNode* prev;
//     Node* node;

//     ListNode() : next(nullptr), prev(nullptr), node(nullptr) {}
//     ListNode(Node* node) : next(nullptr), prev(nullptr), node(node) {}
//     ~ListNode() = default;
// };


// class LinkedList {
//     friend class FibHeap;
//     ListNode* head_;
//     ListNode* tail_;
//     size_t size_;

// public:
//     // constructors and destructors
//     LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}
//     ~LinkedList();

//     // returns number of different degrees of the nodes in list
//     size_t degree() const;
//     void add(Node*);
//     void add(ListNode*);
//     Node* peek();
//     Node* pop();
//     void remove(Node*);
//     void remove(ListNode*);
//     // after merging src is no longer available
//     static void merge(LinkedList& dst, LinkedList& src);
//     bool equal(LinkedList& other) const;
//     bool empty() const;
//     size_t size() const;
// };

// class Node {
//     friend class FibHeap;
//     friend class LinkedList;

//     Node* parent_;
//     bool is_labeled_;
//     ListNode* link_;
// public:
//     int val;
//     LinkedList successors;

//     Node(int val) : val(val), is_labeled_(false), parent_(nullptr), link_(nullptr), successors() {}
//     Node(Node& other) : val(other.val), is_labeled_(other.parent_), link_(other.link_), successors(other.successors) {} 
//     Node& operator=(Node& other);
//     ~Node() = default;

//     void add_child(Node* s) {
//         successors.add(s);
//         s->parent_ = this;
//     }

//     size_t degree() {
//         return successors.size();
//     }
// };

template<typename T>
class FibHeap {

    FibHeapNode<T>* min_node_;
    size_t n_;
    size_t max_degree;

    // free heap
    void free() {
        for (FibHeapNode<T>* root : roots) {
            dfs_delete(root);
        }
    }

    // delete all successors of v
    void dfs_delete(FibHeapNode<T>* v) {

        for (FibHeapNode<T>* node : v->successors){
            dfs_delete(node);
        }        
        // while (!v->successors.empty()) {
        //     FibHeapNode<T>* tmp = v->successors.pop();
        //     dfs_delete(tmp); 
        //     delete tmp;
        // }
        delete v;
    }

    // inserts all successors of v into heap
    void dfs_cpy(FibHeapNode<T>* v) {
        for (FibHeapNode<T>* node : v->successors()){
            dfs_cpy(node);
        }
        insert(v->value);
    }    
    

public:
    list<T> roots;

    // constructors and destructors
    FibHeap() : min_node_(nullptr), n_(0), roots(), max_degree(1) {} 

    FibHeap(const std::vector<T>& data) : n_ { data.size() } { 
        for (size_t i = 0; i < data.size(); i++) {
            insert(data[i]);
        }
    }

    FibHeap(const FibHeap& other) : FibHeap<T>() { 
        for (FibHeapNode<T>* root : other.roots) {
            dfs_cpy(root);
        }
    }
    
    FibHeap<T>& operator=(FibHeap<T>& other) {
        if (this == &other) return *this;

        free();
        for (FibHeapNode<T>* root : other.roots) {
            dfs_cpy(root);
        }
    }

    ~FibHeap() {
        free();  
    }

    // insert val into heap, returns ptr on it
    void insert(const T& val) {
        FibHeapNode<T>* v = new FibHeapNode<T>(val);        
        roots.add(v);
        n_++;
        if (min_node_ == nullptr || val < peek_min()) {
            min_node_ = v;
        }
    }

    void insert(T&& val) {
        FibHeapNode<T>* v = new FibHeapNode<T>(val);
        roots.add(v);
        n_++;
        if (min_node_ == nullptr || val < peek_min()) {
            min_node_ = v;
        }
    }

    void insert(FibHeapNode<T>* node) {
        roots.add(node);
    }

    T& peek_min() {
        if (min_node_ == nullptr) {
            throw std::invalid_argument {"Heap is empty"};
        }
        return min_node_->value;
    }

    // return minimum of val and heap.peek_min() if heap is empty returns val
    T& or_peek_min(const T& val) {
        if (!empty()) {
            return peek_min();
        } else {
            return val;
        }
    } 

    void consolidate() {
        size_t d_n = max_degree + 1;    
        std::vector<FibHeapNode<T>*> a(d_n);
        while (!roots.empty()) {
            FibHeapNode<T>* v = roots.pop();
            size_t deg = v->degree();
            if (deg >= a.capacity()) {
                a.resize(2*deg);
            }

            if (a[deg] == nullptr) {
                a[deg] = v;
            } else {
                FibHeapNode<T>* u = a[deg];
                a[deg] = nullptr;
                if (v->value <= u->value) {
                    v->add_child(u);
                    roots.add(v);
                } else {
                    u->add_child(v);
                    roots.add(u);
                }
            }
        }

        for (FibHeapNode<T>* v : a) {
            if (v == nullptr) continue;
            max_degree = (max_degree >= v->degree()) ? max_degree : v->degree();
            if (min_node_ == nullptr || v->value < min_node_->value) {
                min_node_ = v;
            }
            insert(v);
        } 

    }

    T extract_min() {
        if (empty()) {
            throw std::invalid_argument("Cannot extract min from empty heap");
        }
        roots.remove(min_node_);
        T res = min_node_->value;
        roots.splice(min_node_->successors);
        delete min_node_;
        min_node_ = nullptr;
        consolidate();
        return res;
    }

    void decrease_key(FibHeapNode<T>* s, const T& k) {
        assert(s != nullptr && s->value >= k);
        FibHeapNode<T>* parent = s->parent_;
        s->value = k;
        if ((parent != nullptr) && (k < parent->value)) {
            put_away(s);
        } else if (parent == nullptr && (k < min_node_->value)) {
            min_node_ = s;
        }  
    }

    void splice(FibHeap<T>& src) {
        // TODO
        roots.splice(src.roots);

        if ((!empty() && !src.empty()) && peek_min() > src.peek_min()) {
            min_node_ = src.min_node_;
        }
        if ((empty() && !src.empty())) {
            min_node_ = src.min_node_;
        }
        n_ += src.n_;
    } 

    void put_away(FibHeapNode<T>* s) {
        FibHeapNode<T>* parent = s->parent;
        if (parent) {
            parent->successors.remove(s);
            if (parent->is_labeled_) {
                put_away(parent);
            } else {
                parent->is_labeled_ = true;
            }
        }
        s->parent = nullptr; 
        if (s->val == or_peek_min(s->val)) {
            min_node_ = s;
        }
        addRoot(s);
    }

    void addRoot(FibHeapNode<T>* v) {
        if (v == nullptr) return;
        roots.add(v);
        n_++;

        if (v->value == or_peek_min(v->value)) {
            min_node_ = v;
        }
    }

    bool empty() const {
        return min_node_ == nullptr;
    }
    size_t size() const {
        return n_;
    }
};
