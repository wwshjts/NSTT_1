#include <assert.h>
#include <iostream>
#include <cmath>
#include "fibonacciHeap.h"

LinkedList::~LinkedList() {
    listNode* curr = head_;
    while (curr) { 
        listNode* tmp = curr->next;
        delete(curr);
        curr = tmp;
    }
}

int LinkedList::empty() {
    // is this a good assertion usage? 
    return (head_ == nullptr) && (tail_ == nullptr);
}

size_t const LinkedList::size() {
    return size_;
}

int LinkedList::equal(LinkedList* other) {
    assert(other != nullptr);
    if (this->size() != other->size()) {
        return 0;
    }
    listNode* v1 = this->head_;
    listNode* v2 = other->head_; 
    size_t size = this->size();
    for (size_t i = 0; i < size; i++) {
        if (v1->node->val != v2->node->val) {
            return 0;
        }
    }
    return 1;
}

void LinkedList::add(Node* node) {
    assert(node != nullptr);
    listNode* v = new listNode;
    v->node = node;
    node->link = v;
    if (empty()) {
        head_ = v;
        tail_ = v;
    } else {
        tail_->next = v;
        v->prev = tail_;
        tail_ = v;
    }
    size_++;
}

void LinkedList::remove(Node* node) {
    assert(node != nullptr);
    assert(!empty());
    assert(node->link != nullptr);
    listNode* v = node->link;
    listNode* next = node->link->next;
    listNode* prev = node->link->prev;

    if (next) {
        next->prev = prev;
    } else {
        tail_ = prev;
    }

    if (prev) {
        prev->next = next;
    } else {
        head_ = next;
    }

    size_--;
    node->link = nullptr;
    delete(v);
}

Node* LinkedList::peek() {
    assert(!empty());
    return tail_->node;
}

Node* LinkedList::pop() {
    assert(!empty());
    Node* res = tail_->node;
    remove(res);
    return res;
}

// TODO: I don't know how to implement merge without nulling other list and with O(1) complexity(without copy)
void LinkedList::merge(LinkedList* other) {
    if (other->empty()) return;

    if (this->empty()) {
        this->head_ = other->head_;
        this->tail_ = other->tail_;
        this->size_ = other->size_;
    } else {
        this->tail_->next = other->head_;
        other->head_->prev = this->tail_;
        this->tail_ = other->tail_;
        this->size_ += other->size_;
    }
    other->head_ = nullptr;
    other->tail_ = nullptr;
}


FibHeap::FibHeap(std::vector<int> data): FibHeap() {

    if (data.empty()) return;

    int min;
    for (int item : data) {
        Node* v = new Node(item);
        roots.add(v);
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
        Node* tmp = v->successors.pop();
        DFS_delete(tmp); 
        delete(tmp);
    }
    return;
}

FibHeap::~FibHeap() {
    while(!roots.empty()) {
        Node* v = roots.pop();
        DFS_delete(v);
        delete(v);
    }
}

int FibHeap::empty() {
    return (min_node_ == nullptr) && (roots.empty());
}

Node* FibHeap::insert(int val) {
    Node* v = new Node(val);
    roots.add(v);
    n_++;

    if (min_node_ == nullptr || (peek_min() > val)) {
        min_node_ = v;
    }
    return v;
}

void FibHeap::addRoot(Node* v) {
    if (v == nullptr) return;
    roots.add(v);
    n_++;

    if (v->val == or_peek_min(v->val)) {
        min_node_ = v;
    }
}

void FibHeap::merge(FibHeap* src) {
    this->roots.merge(&src->roots);

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
        Node* v = roots.peek();
        if (a[v->degree()] == nullptr) {
            a[v->degree()] = v;
            roots.remove(v);
        } else {
            Node* w = a[v->degree()];
            a[v->degree()] = nullptr;
            added--;
            roots.remove(v);
            if (v->val <= w->val) {
                v->addChild(w);
                roots.add(v);
            } else {
                w->addChild(v);
                roots.add(w);
            }
        }
    } 

    for (Node* v : a) {
        if (v == nullptr) continue;
        if (min_node_ == nullptr || min_node_->val > v->val) {
            min_node_ = v;
        }

        roots.add(v);
    } 
}

int FibHeap::extract_min() {
    assert(!empty());
    roots.remove(min_node_);
    int res = min_node_->val;
    roots.merge(&min_node_->successors);
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