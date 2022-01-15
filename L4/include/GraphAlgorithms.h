//
// Created by pawel on 12.01.2022.
//

#ifndef L4_GRAPHALGORITHMS_H
#define L4_GRAPHALGORITHMS_H

#include "Graph.h"
#include <bitset>
#include <cmath>
#include <iostream>

class GraphAlgorithms {
public:
    static std::pair<std::vector<long>, std::vector<std::shared_ptr<Edge>>> dijkstra(Graph* g, int s, int d);

    template<int N>
    static Graph* generateHypercube() {
        auto upper = pow(2, N);
        std::cout << static_cast<int>(upper) << '\n';
        auto* g = new Graph(true, static_cast<int>(upper));
        for (int i = 0; i < upper; i++) {
            std::bitset<N> bits(i);

            int h = bits.count();
            int z = N - h;
            for (int j = 0; j < N; j++) {
                int src = static_cast<int>(bits.to_ulong());

                bits[j] = bits[j] == 0 ? 1 : 0;
                int l = std::max(h, z);
                int u = rndCap(l);
                int dest = static_cast<int>(bits.to_ulong());
                if (src < dest) {
                    g->addEdge(src, dest, u, 0);
                }

                bits[j] = !bits[j];
            }
        }
        return g;
    }

    static void edmondsKarp(Graph& g, int s, int t);
    static void shortestAugmentingPath(Graph& g, int s, int t);
    static int rndCap(int l);

private:
    static constexpr long INF = INT64_MAX;

};


#endif //L4_GRAPHALGORITHMS_H
