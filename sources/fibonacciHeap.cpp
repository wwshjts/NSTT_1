#include <assert.h>
#include <iostream>
#include <cmath>
#include "../headers/fibonacciHeap.h"

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

int FibHeap::empty() {
    return (min_node_ == nullptr) && (roots.empty());
}

void FibHeap::insert(int val) {


    Node* v = new Node(val);
    roots.push_back(v);
    n_++;

    if (min_node_ == nullptr || (peek_min() > val)) {
        min_node_ = v;
    }
}

void FibHeap::addNode(Node* v) {
    if (v == nullptr) return;
    roots.push_back(v);
    n_++;
    if (v->val < peek_min()) {
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

size_t FibHeap::d() {
    return ceil(log(n_)) + 1; 
}

void FibHeap::consolidate() {
    size_t d_n = d();    
    std::vector<Node*> a(d_n);

    size_t added = 0;
    
    while (roots.size()) {
        std::cout << "***********\n";
        Node* v = roots.back();
        for (Node* t : a) {
            std::cout << t << " | ";
        }
        std::cout << "\n";
        if (a[v->degree()] == nullptr) {
            a[v->degree()] = v;
            roots.remove(v);
        } else {
            Node* w = a[v->degree()];
            a[v->degree()] = nullptr;
            added--;
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
        addNode(v);
    }
    min_node_ = nullptr;
    consolidate();
    return res;
}