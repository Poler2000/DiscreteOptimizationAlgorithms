//
// Created by Paweł Polerowicz on 09.12.2021.
//

#ifndef L3_GRAPHALGORITHMS_H
#define L3_GRAPHALGORITHMS_H

#include "Graph.h"
#include <bits/stdc++.h>

class GraphAlgorithms {
public:
    static std::vector<long> dijkstra(Graph* g, int s);
    static long dijkstra(Graph* g, int s, int d);
    static std::vector<long> dial(Graph* g, int s, int C);
    static long dial(Graph* g, int s, int d, int C);
    static std::vector<long> radix(Graph* g, int s, int C);
    static long radix(Graph* g, int s, int d, int C);

private:
    static constexpr long INF = INT64_MAX;
};


#endif //L3_GRAPHALGORITHMS_H
