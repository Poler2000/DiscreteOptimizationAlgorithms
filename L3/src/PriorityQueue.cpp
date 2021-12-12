#include <iostream>
#include "../include/PriorityQueue.h"

void PriorityQueue::insert(long x, long p) {
    long i = A.size();
    A.push_back({x, INT64_MAX});
    while (i > 0 && A[parent(i)].priority > p) {
        A[i] = A[parent(i)];
        i = parent(i);
    }
    A[i].val = x;
    A[i].priority = p;
}

bool PriorityQueue::empty() {
    return A.empty();
}

long PriorityQueue::top() {
    return A.empty() ? -1 : A[0].val;
}

long PriorityQueue::pop() {
    long res = A.empty() ? -1 : A[0].val;
    if (A.empty()) {
        return res;
    }
    A[0] = A[A.size() - 1];
    A.pop_back();
    heapify(0);
    return res;
}

void PriorityQueue::priority(long x, long p) {
    for (long i = 0; i < A.size(); i++) {
        if (A[i].val == x && A[i].priority > p) {
            A[i].priority = p;
            long j = i;
            while (j > 0 && A[parent(j)].priority > A[j].priority) {
                std::swap(A[parent(j)], A[j]);
                j = parent(j);
            }
            //heapify(0);
        }
    }
}

void PriorityQueue::prlong() {
    for (auto &i : A) {
        std::printf("(val: %d; p: %d) ", i.val, i.priority);
    }
}

/*
 * produces exactly the same asm output as
 * return (i << 1) + 1; with better readability
 */
long PriorityQueue::left(const long i) {
    return (i * 2) + 1;
}

/*
 * produces exactly the same asm output as
 * return (i + 1) << 1; with better readability
 */
long PriorityQueue::right(const long i) {
    return (i + 1) * 2;
}

/*
 * longerestingly, produces the following output (via clang -O3):
 *
        lea     eax, [rdi - 1]
        sar     eax
        ret
 *
 *  whereas
 *  return (i - 1) / 2;
 *  produces:
 *
        mov     eax, edi
        add     eax, -1
        shr     eax, 31
        add     eax, edi
        add     eax, -1
        sar     eax
        ret
 *
 * effectiveness is the subject for further investigation
 * @param i
 * @return
 */
long PriorityQueue::parent(const long i) {
    return (i - 1) >> 1;
}

void PriorityQueue::buildHeap() {
    for (size_t i = (A.size() - 1) / 2; i > -1; i--) {
        heapify(i);
    }
}

void PriorityQueue::heapify(long i) {
    long l = left(i);
    long r = right(i);
    long maxPriority;
    if (l < A.size() && A[l].priority < A[i].priority) {
        maxPriority = l;
    }
    else {
        maxPriority = i;
    }
    if (r < A.size() && A[r].priority < A[maxPriority].priority) {
        maxPriority = r;
    }
    if (maxPriority != i) {
        std::swap(A[i], A[maxPriority]);
        heapify(maxPriority);
    }
}

