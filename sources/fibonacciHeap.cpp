#include <assert.h>
#include <iostream>
#include <cmath>
#include <set>
#include "fibonacciHeap.h"

Node& Node::operator=(Node& other) {
    if (this == &other) {
        return *this;
    }
    this->val = other.val;
    this->link_ = other.link_;
    this->is_labeled_ = other.is_labeled_;
    // some recursion stuff
    this->successors = other.successors;
    return *this;
}

LinkedList::~LinkedList() {
    ListNode* curr = head_;
    while (curr) { 
        ListNode* tmp = curr->next;
        delete curr;
        curr = tmp;
    }
}

bool LinkedList::empty() const {
    return (head_ == nullptr) && (tail_ == nullptr);
}

size_t LinkedList::size() const {
    return size_;
}

size_t LinkedList::degree() const {
    ListNode* curr = head_;
    std::set<size_t> d;
    while (curr) {
        d.insert(curr->node->degree());
        curr = curr->next;
    }
    return d.size();
}

bool LinkedList::equal(LinkedList& other) const {
    if (size() != other.size()) {
        return 0;
    }
    ListNode* v1 = head_;
    ListNode* v2 = other.head_; 
    size_t size = size_;
    for (size_t i = 0; i < size; i++) {
        if (v1->node->val != v2->node->val) {
            return false;
        }
    }
    return true;
}

void LinkedList::add(ListNode* v) {
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

void LinkedList::add(Node* node) {
    assert(node != nullptr);
    ListNode* v = new ListNode;
    v->node = node;
    node->link_ = v;
    add(v);
}

void LinkedList::remove(ListNode* v) {
    assert(v != nullptr);
    assert(!empty());

    ListNode* next = v->next;
    ListNode* prev = v->prev;

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
    v->node->link_ = nullptr;
    delete v;
}


void LinkedList::remove(Node* node) {
    assert(node->link_ != nullptr);
    remove(node->link_);
}

Node* LinkedList::peek() {
    assert(!empty());
    return tail_->node;
}

Node* LinkedList::pop() {
    assert(!empty());
    Node* res = tail_->node;
    remove(tail_);
    return res;
}

// TODO: I don't know how to implement merge without nulling other list and with O(1) complexity(without copy)
void LinkedList::merge(LinkedList& dst, LinkedList& src) {
    if (src.empty()) return;

    if (dst.empty()) {
        dst.head_ = src.head_;
        dst.tail_ = src.tail_;
        dst.size_ = src.size_;
    } else {
        dst.tail_->next = src.head_;
        src.head_->prev = dst.tail_;
        dst.tail_ = src.tail_;
        dst.size_ += src.size_;
    }
    src.head_ = nullptr;
    src.tail_ = nullptr;
}


FibHeap::FibHeap(std::vector<int>& data): FibHeap() {

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

FibHeap::FibHeap(FibHeap& other) : FibHeap() {
    ListNode* src = other.roots.head_;     
    while (src) {
        dfs_cpy(src);
        src = src->next;
    }
}

FibHeap& FibHeap::operator=(FibHeap& other) {
    if (this == &other) return *this;
    while(!roots.empty()) {
        Node* v = roots.pop();
        dfs_delete(v);
        delete v;
    }

    ListNode* src = other.roots.head_;     
    while (src) {
        dfs_cpy(src);
        src = src->next;
    }

    return *this; 
}

// copies all node successors
void FibHeap::dfs_cpy(ListNode* v) { 
    ListNode* curr =  v->node->successors.head_;

    while (curr) {
        dfs_cpy(curr);
        insert(curr->node->val);
        curr = curr->next;
    }
    insert(v->node->val);
}

// recursively deletes all nodes in a tree
void FibHeap::dfs_delete(Node* v) {
    while (!v->successors.empty()) {
        Node* tmp = v->successors.pop();
        dfs_delete(tmp); 
        delete tmp;
    }
}

FibHeap::~FibHeap() {
    while(!roots.empty()) {
        Node* v = roots.pop();
        dfs_delete(v);
        delete v;
    }
}

bool FibHeap::empty() const {
    return (min_node_ == nullptr) && (roots.empty());
}

size_t FibHeap::degrees() const {
    return roots.degree();
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

void FibHeap::merge(FibHeap& src) {
    LinkedList::merge(roots, src.roots);

    if ((!empty() && !src.empty()) && peek_min() > src.peek_min()) {
        min_node_ = src.min_node_;
    }
    if ((empty() && !src.empty())) {
        min_node_ = src.min_node_;
    }
    n_ += src.n_;
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

size_t FibHeap::d() const {
    return ceil(log(n_)) + 1; 
}

void FibHeap::consolidate() {
    size_t d_n = d() + 1;    
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
    LinkedList::merge(roots, min_node_->successors);
    delete min_node_;
    min_node_ = nullptr;
    consolidate();
    return res;
}

void FibHeap::put_away(Node* s) {
    Node* parent = s->parent_;
    if (parent) {
        parent->successors.remove(s);
        if (parent->is_labeled_) {
            put_away(parent);
        } else {
            parent->is_labeled_ = true;
        }
    }
    s->parent_ = nullptr; 
    if (s->val == or_peek_min(s->val)) {
        min_node_ = s;
    }
    addRoot(s);
}

void FibHeap::decrease_key(Node* s, int k) {
    assert(s != nullptr && s->val >= k);
    Node* parent = s->parent_;
    s->val = k;
    if ((parent != nullptr) && (k < parent->val)) {
        put_away(s);
    } else if (parent == nullptr && k < min_node_->val) {
        min_node_ = s;
    }
}