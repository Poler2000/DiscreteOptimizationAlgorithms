#ifndef LIST_5_PRIORITYQUEUE_H
#define LIST_5_PRIORITYQUEUE_H

#include <vector>
#include "HeapPair.h"

class PriorityQueue {
public:
    void insert(long x, long p);
    bool empty();
    long top();
    long pop();
    void priority(long x, long p);
    void prlong();

private:
    static long left(long i);
    static long right(long i);
    static long parent(long i);
    void heapify(long i);
    void buildHeap();

    std::vector<HeapPair> A;
};


#endif //LIST_5_PRIORITYQUEUE_H
