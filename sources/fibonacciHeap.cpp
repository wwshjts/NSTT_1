#include <assert.h>
#include "../headers/fibonacciHeap.h"

int FibHeap::empty() {
    return (min_node_ == nullptr) && (roots.empty());
}

int FibHeap::peek_min() {
    assert(empty());
    return min_node_->val;
}

void FibHeap::insert(int val) {
    Node* v = new Node(val);
    roots.push_back(v);

    if (min_node_ == nullptr || (peek_min() > val)) {
        min_node_ = v;
    }
}

void FibHeap::merge(FibHeap* dst, FibHeap* src) {
    dst->roots.merge(src->roots);

    if ((!dst->empty() && !src->empty()) && dst->peek_min() > src->peek_min()) {
        dst->min_node_ = src->min_node_;
    }
    if ((dst->empty() && !src->empty())) {
        dst->min_node_ = src->min_node_;
    }
}
