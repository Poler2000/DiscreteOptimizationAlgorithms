//
// Created by pawel on 12.01.2022.
//

#include "GraphAlgorithms.h"
#include "Timer.h"

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

GraphAlgorithms::Result GraphAlgorithms::edmondsKarp(Graph& g, int s, int t, bool printFlow) {
    long long flow = 0;
    const int n = g.getNumberOfVertices();
    auto pair = dijkstra(&g, s, t);
    auto& d = pair.first;
    auto& pred = pair.second;
    long long paths = 0;
    Timer t1;
    int it = 0;
    do {
        it++;
        for (int i = 0; i < n; i++) {
            pred[i] = nullptr;
        }

        std::vector<bool> visited(n);
        dfs(g, s, s, t, visited, pred);

        // bfs version - not effective
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

        if (pred[t] != nullptr) {
            paths++;
            int df = INT32_MAX;
            for (auto e = pred[t]; e != nullptr; e = pred[e->source]) {
                df = std::min(df, e->u - e->f);
            }

            for (auto e = pred[t]; e != nullptr; e = pred[e->source]) {
                e->f += df;
                if (e->u == e->f) {
                    if (printFlow) {
                        std::cout << e->source << " -> " << e->dest << ' ' << e->f << '/' << e->u << '\n';
                    }
                    g.removeEdge(e->source, e->dest);
                }
            }
            flow += df;
        }
    } while (pred[t] != nullptr);

    if (printFlow) {
        for (int i = 0; i < n; i++) {
            for (auto n : g.getEdges(i)) {
                std::cout << n->source << " -> " << n->dest << ' ' << n->f << '/' << n->u << '\n';
            }
        }
    }

    std::cout << "Flow is: " << flow << '\n';
    std::cout << "time is: " << t1.getTimeInMicroseconds().count() << '\n';
    return {t1.getTimeInMicroseconds().count(), paths, flow};
}

int GraphAlgorithms::rndCap(int l) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, static_cast<int>(pow(2, l)));

    return dis(gen);
}

GraphAlgorithms::Result GraphAlgorithms::shortestAugmentingPath(Graph &g, int s, int t, bool printFlow) {
    long long flow = 0;
    Timer t1;
    const int n = g.getNumberOfVertices();
    auto pair = dijkstra(&g, s, t);
    auto& d = pair.first;
    auto& pred = pair.second;
    int curr = s;
    long long paths = 0;
    while (d[s] < n) {
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
            if (printFlow) {
                auto e = g.getEdge(curr, prev);
                if (e != nullptr) {
                    std::cout << e->source << " -> " << e->dest << ' ' << e->f << '/' << e->u << '\n';
                }
            }
            g.removeEdge(curr, prev);
        } else {
            if (curr == t) {
                paths++;
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
                        }
                        if (e->u == e->f) {
                            if (printFlow) {
                                std::cout << e->source << " -> " << e->dest << ' ' << e->f << '/' << e->u << '\n';
                            }
                            g.removeEdge(e->source, e->dest);
                        }
                    }
                    flow += df;
                }
                curr = s;
            }
        }
    }

    if (printFlow) {
        for (int i = 0; i < n; i++) {
            for (auto n : g.getEdges(i)) {
                std::cout << n->source << " -> " << n->dest << ' ' << n->f << '/' << n->u << '\n';
            }
        }
    }

    std::cout << "Flow is: " << flow << '\n';
    std::cout << "time is: " << t1.getTimeInMicroseconds().count() << '\n';
    return {t1.getTimeInMicroseconds().count(), paths, flow};
}
