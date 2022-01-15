//
// Created by pawel on 12.01.2022.
//

#include "GraphAlgorithms.h"
#include "Timer.h"

#include <bitset>
#include <queue>
#include <algorithm>
#include <random>
#include "PriorityQueue.h"

std::pair<std::vector<long>, std::vector<std::shared_ptr<Edge>>> GraphAlgorithms::dijkstra(Graph* g, int s, int t) {
    size_t n = g->getNumberOfVertices();
    // distance labels
    std::vector<long> d(n);
    // predecessors
    std::vector<std::shared_ptr<Edge>> pred(n);
    PriorityQueue q;

    for (size_t i = 0; i < n; i++) {
        d[i] = INF;
    }
    d[s] = 0;
    pred[s] = nullptr;
    for (size_t i = 0; i < n; i++) {
        q.insert(i, d[i]);
    }

    while(!q.empty()) {
        int u = q.pop();
        auto edges = g->getEdges(u);
        for (auto& e : edges) {
            if (d[e->dest] > d[u] + e->w) {
                d[e->dest] = d[u] + e->w;
                pred[e->dest] = e;
                q.priority(e->dest, d[e->dest]);
            }
        }
    }
    return std::make_pair(d, pred);
}

void dfs(Graph& g, int v, int s, int t, std::vector<bool>& visited, std::vector<std::shared_ptr<Edge>>& pred) {
    visited[v] = true;
    if (visited[t]) {
        return;
    }

    auto edges = g.getEdges(v);
    for (auto& e : edges) {
        if (!visited[e->dest]) {
            if (pred[e->dest] == nullptr && e->dest != s && e->u > e->f) {
                pred[e->dest] = e;
            }
            dfs(g, e->dest, s, t, visited, pred);
        }
    }
}

void GraphAlgorithms::edmondsKarp(Graph& g, int s, int t) {
    long long flow = 0;
    const int n = g.getNumberOfVertices();
    auto pair = dijkstra(&g, s, t);
    auto& d = pair.first;
    auto& pred = pair.second;
    Timer t1;
    int it = 0;
    do {
        it++;
        // bfs
        Timer t2;
        for (int i = 0; i < n; i++) {
            pred[i] = nullptr;
        }

        std::vector<bool> visited(n);
        dfs(g, s, s, t, visited, pred);

        /*std::queue<int> q;
        q.push(s);

       while (!q.empty()) {
            int curr = q.front();
            q.pop();
            auto edges = g.getEdges(curr);
            for (auto& e : edges) {
                if (pred[e->dest] == nullptr && e->dest != s && e->u > e->f) {
                    pred[e->dest] = e;
                    q.push(e->dest);
                }
            }
        }*/

        Timer t4;

        if (pred[t] != nullptr) {
            int df = INT32_MAX;
            for (auto e = pred[t]; e != nullptr; e = pred[e->source]) {
                df = std::min(df, e->u - e->f);
            }

            for (auto e = pred[t]; e != nullptr; e = pred[e->source]) {
                e->f += df;
                if (g.edgeExist(e->dest, e->source)) {
                    auto r = g.getEdge(e->dest, e->source);
                    r->f -= df;
                } /*else {
                    g.addEdge(e->dest, e->source, -df, 0);
                }*/
                if (e->u == e->f) {
                    g.removeEdge(e->source, e->dest);
                }
            }
            flow += df;

        }
        //std::cout << pred[t]->source << '\n';

    } while (pred[t] != nullptr);
    std::cout << "Flow is: " << flow << '\n';
    std::cout << "time is: " << t1.getTimeInMicroseconds().count() << '\n';
}

int GraphAlgorithms::rndCap(int l) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, static_cast<int>(pow(2, l)));

    return dis(gen);
}

void GraphAlgorithms::shortestAugmentingPath(Graph &g, int s, int t) {
    long long flow = 0;
    int x = 0;
    Timer t1;
    const int n = g.getNumberOfVertices();
    auto pair = dijkstra(&g, s, t);
    auto& d = pair.first;
    auto& pred = pair.second;
    int curr = s;
    std::cout << "let's begin\n";
    std::cout << 0 << ' ' << d[0] << '\n';
    for (int i = 1; i < n; i++) {
        std::cout << i << ' ' << d[i] << ' ' << pred[i]->source << '\n';
    }
    while (d[s] < n) {
        //std::cout << curr << '\n';
        auto edges = g.getEdges(curr);
        bool isAdmissibleArc = false;
        for (auto& e : edges) {
            if (d[e->dest] == d[e->source] + 1) {
                isAdmissibleArc = true;
                pred[e->dest] = e;
                curr = e->dest;
                break;
            }
        }
        if (!isAdmissibleArc) {
            auto edges = g.getEdges(curr);
            int df = INT32_MAX;
            for (auto& e : edges) {
                if ((e->u - e->f) > 0) {
                    df = std::min(df, (int)(d[e->dest] + 1));
                }
            }
            d[curr] = df;
            int prev = curr;
            if (curr != s) {
                curr = pred[curr]->source;
            }
            g.removeEdge(curr, prev);
        } else {
            if (curr == t) {
                if (pred[t] != nullptr) {
                    int df = INT32_MAX;
                    for (auto e = pred[t]; e != nullptr; e = pred[e->source]) {
                        df = std::min(df, e->u - e->f);
                    }
                    for (auto e = pred[t]; e != nullptr; e = pred[e->source]) {
                        e->f += df;
                        if (g.edgeExist(e->dest, e->source)) {
                            auto r = g.getEdge(e->dest, e->source);
                            r->f -= df;
                        } /*else {
                    g.addEdge(e->dest, e->source, -df, 0);
                }*/
                        if (e->u == e->f) {
                            g.removeEdge(e->source, e->dest);
                        }
                    }
                    flow += df;
                }
                curr = s;
            }
        }
    }

    std::cout << "Flow is: " << flow << '\n';
    std::cout << "time is: " << t1.getTimeInMicroseconds().count() << '\n';
}
