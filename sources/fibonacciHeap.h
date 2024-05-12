#include <stdexcept>
#include <vector>
#include <list>
#include <set>
#include <exception>
#include <iostream>
#include <deque>

template<typename T>
class list;

// just wrapper for type T
template<typename T>
struct FibHeapNode {
    T value;
    FibHeapNode<T>* parent = nullptr;
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
        node->parent = this;
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
    list() = default;

    list<T>(list<T>&& other) : inner_ {std::move(other.inner_)} {}

    list<T>& operator=(list<T>&& other) {
        inner_ = std::move(other.inner_);        
        return *this;
    }

    void add(FibHeapNode<T>* node) {
        node->link = inner_.insert(inner_.end(), node);
    }

    // after this link is invalid
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

    class iterator {
        FibHeapNode<T>* curr_node_;
        typename std::list<FibHeapNode<T>*>::iterator curr_root_;
        std::deque<FibHeapNode<T>*> que_;

    public:  
        iterator(typename std::list<FibHeapNode<T>*>::iterator root) : curr_node_ { nullptr }, curr_root_ { root } {}

        void fill_que() {
            for(FibHeapNode<T>* node : curr_node_->successors) {
                que_.push_back(node);
            }
        }


        const T& operator++() {
            FibHeapNode<T>* res;
            if (curr_node_ == nullptr) {
                curr_node_ = *(curr_root_);
            } else {
                curr_node_ = que_.front();
                que_.pop_front();
            }

            fill_que();
            res = curr_node_;

            if (que_.empty()) {
                ++curr_root_;
                curr_node_ = nullptr;
            }

            return res->value;
        }

        const T& operator*() {
            if (curr_node_ == nullptr) {
                return (*curr_root_)->value;
            } else {
                return que_.front()->value;
            }

        }

        const T* operator->() {
            if (curr_node_ == nullptr) {
                return ((*curr_root_)->value);
            } else {
                return &(que_.front()->value);
            }
        }

        bool operator!=(const iterator& other) {
            return curr_root_ != other.curr_root_; 
        }
    };
;
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
    };

    FibHeap(FibHeap<T>&& other) : 
        min_node_ { other.min_node_ },
        n_ { other.n_ },
        max_degree { other.max_degree }, 
        roots { std::move(other.roots) } {}

    FibHeap<T>& operator=(FibHeap<T>&& other) {
        min_node_ = other.min_node_;
        n_ = other.n_;
        max_degree = other.max_degree;
        roots = std::move(other.roots);
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

    // iterator things
    const iterator begin() {
        return iterator(roots.begin());
    }

    const iterator end() {
        return iterator(roots.end());        
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
        n_++;

        if (min_node_ == nullptr || node->value < peek_min()) {
            min_node_ = node;
        }
    }

    FibHeapNode<T>* insert_node(const T& val) {
        FibHeapNode<T>* v = new FibHeapNode<T>(val);        
        roots.add(v);
        n_++;
        if (min_node_ == nullptr || val < peek_min()) {
            min_node_ = v;
        }
        return v;
    }

    T& peek_min() {
        if (min_node_ == nullptr) {
            throw std::invalid_argument {"Heap is empty"};
        }
        return min_node_->value;
    }

    // return minimum of val and heap.peek_min() if heap is empty returns val
    T& or_peek_min(T& val) {
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
                    addRoot(v);
                } else {
                    u->add_child(v);
                    addRoot(u);
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
        n_--;
        return res;
    }

    void decrease_key(FibHeapNode<T>* s, const T& k) {
        assert(s != nullptr && s->value >= k);
        FibHeapNode<T>* parent = s->parent;
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
            if (parent->is_labeled) {
                put_away(parent);
            } else {
                parent->is_labeled = true;
            }
        }
        s->parent = nullptr; 
        if (s->value == or_peek_min(s->value)) {
            min_node_ = s;
        }
        addRoot(s);
    }

    void addRoot(FibHeapNode<T>* v) {
        if (v == nullptr) return;
        roots.add(v);
        v->parent = nullptr;
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
