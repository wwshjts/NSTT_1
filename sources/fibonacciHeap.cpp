#include <assert.h>
#include <iostream>
#include <cmath>
#include "fibonacciHeap.h"

FibHeap::FibHeap(std::vector<int> data): FibHeap() {

    if (data.empty()) return;

    int min;
    for (int item : data) {
        Node* v = new Node(item);
        roots.push_back(v);
        n_++;
        if (min_node_ == nullptr || min > item) {
            min_node_ = v;
            min = item;
        }
    }
}
// recursively deletes all nodes in a tree
void FibHeap::DFS_delete(Node* v) {
    while (!v->successors.empty()) {
        Node* tmp = v->successors.front();
        v->successors.pop_front();
        DFS_delete(tmp); 
        delete(tmp);
    }
    return;
}

FibHeap::~FibHeap() {
    while(!roots.empty()) {
        Node* v = roots.front();
        roots.pop_front();
        DFS_delete(v);
        delete(v);
    }
    std::cout << "Done dstr " << roots.empty() << "\n";
}

int FibHeap::empty() {
    return (min_node_ == nullptr) && (roots.empty());
}

Node* FibHeap::insert(int val) {
    Node* v = new Node(val);
    roots.push_back(v);
    n_++;

    if (min_node_ == nullptr || (peek_min() > val)) {
        min_node_ = v;
    }
    return v;
}

void FibHeap::addRoot(Node* v) {
    if (v == nullptr) return;
    roots.push_back(v);
    n_++;

    if (v->val == or_peek_min(v->val)) {
        min_node_ = v;
    }
}

void FibHeap::merge(FibHeap* src) {
    this->roots.merge(src->roots);

    if ((!this->empty() && !src->empty()) && this->peek_min() > src->peek_min()) {
        this->min_node_ = src->min_node_;
    }
    if ((this->empty() && !src->empty())) {
        this->min_node_ = src->min_node_;
    }
    this->n_ += src->n_;
}

int FibHeap::peek_min() {
    assert(!empty());
    return min_node_->val;
}

int FibHeap::or_peek_min(int val) {
    if (empty()) {
        return val;
    } else {
        return (val <= peek_min()) ? val : peek_min();
    }
}

size_t FibHeap::d() {
    return ceil(log(n_)) + 1; 
}

void FibHeap::consolidate() {
    size_t d_n = d();    
    std::vector<Node*> a(d_n);

    size_t added = 0;
    
    while (roots.size()) {
        Node* v = roots.back();
        if (a[v->degree()] == nullptr) {
            a[v->degree()] = v;
            // TODO
            roots.remove(v);
        } else {
            Node* w = a[v->degree()];
            a[v->degree()] = nullptr;
            added--;
            // TODO
            roots.remove(w);
            roots.remove(v);
            if (v->val <= w->val) {
                v->addChild(w);
                roots.push_back(v);
            } else {
                w->addChild(v);
                roots.push_back(w);
            }
        }
    } 

    for (Node* v : a) {
        if (v == nullptr) continue;
        if (min_node_ == nullptr || min_node_->val > v->val) {
            min_node_ = v;
        }

        roots.push_back(v);
    } 
}

int FibHeap::extract_min() {
    assert(!empty());
    // TODO
    roots.remove(min_node_);
    int res = min_node_->val;
    for (Node* v : min_node_->successors) {
        addRoot(v);
    }
    delete(min_node_);
    min_node_ = nullptr;
    consolidate();
    return res;
}

void FibHeap::put_away(Node* s) {
    Node* parent = s->parent;
    if (parent) {
        parent->successors.remove(s);
        if (parent->is_labeled) {
            put_away(parent);
        } else {
            parent->is_labeled = true;
        }
    }
    s->parent = nullptr; 
    if (s->val == or_peek_min(s->val)) {
        min_node_ = s;
    }
    addRoot(s);
}

void FibHeap::decrease_key(Node* s, int k) {
    assert(s != nullptr && s->val >= k);
    Node* parent = s->parent;
    s->val = k;
    if ((parent != nullptr) && (k < parent->val)) {
        put_away(s);
    } else if (parent == nullptr && k < min_node_->val) {
        min_node_ = s;
    }
}