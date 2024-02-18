#include "../headers/fibonacciHeap.h"

void FibHeap::insert(int val) {
    Node* v = new Node(val);
    roots.push_back(v);
}

void FibHeap::merge(FibHeap* dst, FibHeap* src) {
    dst->roots.merge(src->roots);
}
