//
// Created by pawel on 09.12.2021.
//

#include "../include/GraphAlgorithms.h"
#include "../include/PriorityQueue.h"
#include "../include/Timer.h"
#include "../include/Bucket.h"

#include <list>

std::vector<long> GraphAlgorithms::dijkstra(Graph* g, int s) {
    size_t n = g->getNumberOfVertices();
    // distance labels
    std::vector<long> d(n + 1);
    // predecessors
    std::vector<int> pred(n + 1);
    PriorityQueue q;

    for (size_t i = 1; i < n + 1; i++) {
        d[i] = INF;
    }
    d[s] = 0;
    pred[s] = s;
    for (size_t i = 1; i < n + 1; i++) {
        q.insert(i, d[i]);
    }

    while(!q.empty()) {
        int u = q.pop();
        auto edges = g->getEdges(u);
        for (auto& e : edges) {
            if (d[e.dest] > d[u] + e.w) {
                d[e.dest] = d[u] + e.w;
                pred[e.dest] = u;
                q.priority(e.dest, d[e.dest]);
            }
        }
    }
    return d;
}

std::vector<long> GraphAlgorithms::dial(Graph *g, int s, int C) {
    size_t n = g->getNumberOfVertices();
    size_t nC = C + 1;
    int visited = 0;
    // distance labels
    std::vector<std::pair<long, std::list<int>::iterator> > d(n + 1);
    // predecessors
    std::vector<int> pred(n + 1);
    // cups
    std::vector<std::list<int>> content(nC);
    for (size_t i = 1; i < n + 1; i++) {
        d[i].first = INF;
    }
    d[s].first = 0;
    pred[s] = s;
    content[0].push_back(s);
    long i = 0;
    while(visited < n) {
        while (content[i % nC].empty() && i < nC * n) {
            i++;
        }
        if (i >= nC * n) {
            break;
        }

        do {
            int u = content[i % nC].front();
            visited++;
            content[i % nC].pop_front();

            auto edges = g->getEdges(u);

            for (auto& e : edges) {
                if (d[e.dest].first > d[u].first + e.w) {
                    if (d[e.dest].first != INF) {
                        content[d[e.dest].first % nC].erase(d[e.dest].second);
                    }

                    d[e.dest].first = d[u].first + e.w;
                    pred[e.dest] = u;

                    content[d[e.dest].first % nC].push_front(e.dest);
                    d[e.dest].second = content[d[e.dest].first % nC].begin();
                }
            }
        } while (!content[i % nC].empty());

    }
    std::vector<long> distance(n);
    for (size_t i = 1; i < n + 1; i++) {
        distance[i - 1] = d[i].first;
    }

    return distance;
}

std::vector<long> GraphAlgorithms::radix(Graph *g, int s, int C) {
    size_t n = g->getNumberOfVertices();
    int visited = 0;
    std::vector<std::pair<long, std::list<int>::iterator>> d(n + 1);
    std::vector<int> pred(n + 1);
    size_t nofBuckets = (size_t)std::log2(C) + 2;
    std::vector<Bucket2> content(nofBuckets);

    content[0].minLabel = 0;
    content[0].maxLabel = 0;

    for (size_t i = 0; i < nofBuckets - 1; i++) {
        content[i + 1].minLabel = pow(2, i);
        content[i + 1].maxLabel = pow(2, i + 1) - 1;
        content[i + 1].content = std::list<int>();
    }
    for (size_t i = 1; i < n + 1; i++) {
        d[i].first = INF;
    }

    d[s].first = 0;
    pred[s] = s;
    content[0].content = std::list<int>();
    content[0].content.push_front(s);
    d[s].second = content[0].content.begin();
    content[0].elements = 1;

    // main loop
    while(visited < n) {
        long i = 0;
        while (content[i].elements < 1 && i < nofBuckets) {
            i++;
        }
        if (i >= nofBuckets) {
            break;
        }
        long minLabel = INF;
        long u;
        // find u with min label
        for (auto& c: content[i].content) {
            if (d[c].first < minLabel) {
                minLabel = d[c].first;
                u = c;
            }
        }
        content[i].content.remove(u);
        content[i].elements--;
        visited++;
        minLabel = d[u].first - content[0].minLabel;

        // update labels
        for (auto& b: content) {
            b.minLabel += minLabel;
            b.maxLabel += minLabel;
        }

        // move nodes to correct cup
        for (int j = 1; j < nofBuckets; j++) {
            if (content[j].elements > 0) {
                int e = content[j].elements;
                for (int k = 0; k < e; k++) {
                    int node = content[j].content.front();
                    content[j].content.pop_front();
                    content[j].elements--;
                    int l = j;
                    while (content[l].minLabel > d[node].first) {
                        l--;
                    }
                    content[l].content.push_back(node);
                    d[node].second = content[l].content.end();
                    content[l].elements += 1;
                }
            }
        }
        auto edges = g->getEdges(u);

        // we search edges from u
        for (auto& e : edges) {
            if (d[e.dest].first > d[u].first + e.w) {
                // is node already in one of cups?
                if (d[e.dest].first != INF) {
                    int j = 0;
                    while (content[j].maxLabel < d[e.dest].first) {
                        j++;
                    }
                    content[j].content.remove(e.dest);
                    content[j].elements--;
                }

                d[e.dest].first = d[u].first + e.w;
                pred[e.dest] = u;
                int j = 0;
                while (content[j].maxLabel < d[e.dest].first) {
                    j++;
                }
                content[j].content.push_front(e.dest);
                content[j].elements++;

                d[e.dest].second = content[j].content.begin();
            }
        }
    }

    // postprocessing
    std::vector<long> distance(n);
    for (size_t i = 1; i < n + 1; i++) {
        distance[i - 1] = d[i].first;
    }

    return distance;
}

long GraphAlgorithms::dijkstra(Graph *g, int s, int goal) {
    size_t n = g->getNumberOfVertices();
    std::vector<long> d(n + 1);
    std::vector<int> pred(n + 1);
    PriorityQueue q;

    for (size_t i = 1; i < n + 1; i++) {
        d[i] = INF;
    }
    d[s] = 0;
    pred[s] = s;
    for (size_t i = 1; i < n + 1; i++) {
        q.insert(i, d[i]);
    }

    while(!q.empty()) {
        int u = q.pop();
        if (u == goal) {
            break;
        }
        auto edges = g->getEdges(u);
        for (auto& e : edges) {
            if (d[e.dest] > d[u] + e.w) {
                d[e.dest] = d[u] + e.w;
                pred[e.dest] = u;
                q.priority(e.dest, d[e.dest]);
            }
        }
    }
    return d[goal];
}

long GraphAlgorithms::dial(Graph *g, int s, int goal, int C) {
    size_t n = g->getNumberOfVertices();
    size_t nC = C + 1;
    int visited = 0;
    std::vector<std::pair<long, std::list<int>::iterator> > d(n + 1);
    std::vector<int> pred(n + 1);
    std::vector<std::list<int>> content(nC);
    for (size_t i = 1; i < n + 1; i++) {
        d[i].first = INF;
    }
    d[s].first = 0;
    pred[s] = s;
    content[0].push_back(s);
    long i = 0;
    while(visited < n) {
        while (content[i % nC].empty() && i < nC * n) {
            i++;
        }
        if (i >= nC * n) {
            break;
        }

        do {
            int u = content[i % nC].front();
            if (u == goal) {
                d[goal].first;
            }
            visited++;
            content[i % nC].pop_front();

            auto edges = g->getEdges(u);

            for (auto& e : edges) {
                if (d[e.dest].first > d[u].first + e.w) {
                    if (d[e.dest].first != INF) {
                        content[d[e.dest].first % nC].erase(d[e.dest].second);
                    }

                    d[e.dest].first = d[u].first + e.w;
                    pred[e.dest] = u;

                    content[d[e.dest].first % nC].push_front(e.dest);
                    d[e.dest].second = content[d[e.dest].first % nC].begin();
                }
            }
        } while (!content[i % nC].empty());

    }

    return d[goal].first;
}

long GraphAlgorithms::radix(Graph *g, int s, int goal, int C) {
    size_t n = g->getNumberOfVertices();
    int visited = 0;
    std::vector<std::pair<long, std::list<int>::iterator>> d(n + 1);
    std::vector<int> pred(n + 1);
    size_t nofBuckets = (size_t)std::log2(C) + 2;
    std::vector<Bucket2> content(nofBuckets);
    content[0].minLabel = 0;
    content[0].maxLabel = 0;
    for (size_t i = 0; i < nofBuckets - 1; i++) {
        content[i + 1].minLabel = pow(2, i);
        content[i + 1].maxLabel = pow(2, i + 1) - 1;
        content[i + 1].content = std::list<int>();
    }
    for (size_t i = 1; i < n + 1; i++) {
        d[i].first = INF;
    }
    d[s].first = 0;
    pred[s] = s;
    content[0].content = std::list<int>();
    content[0].content.push_front(s);
    d[s].second = content[0].content.begin();
    content[0].elements = 1;
    while(visited < n) {
        long i = 0;
        while (content[i].elements < 1 && i < nofBuckets) {
            i++;
        }
        if (i >= nofBuckets) {
            break;
        }
        long minLabel = INF;
        long u;
        for (auto& c: content[i].content) {
            if (d[c].first < minLabel) {
                minLabel = d[c].first;
                u = c;
            }
        }
        if (u == goal) {
            break;
        }
        content[i].content.remove(u);
        content[i].elements--;
        visited++;
        minLabel = d[u].first - content[0].minLabel;
        for (auto& b: content) {
            b.minLabel += minLabel;
            b.maxLabel += minLabel;
        }
        for (int j = 1; j < nofBuckets; j++) {
            if (content[j].elements > 0) {
                int e = content[j].elements;
                for (int k = 0; k < e; k++) {
                    int node = content[j].content.front();
                    content[j].content.pop_front();
                    content[j].elements--;
                    int l = j;
                    while (content[l].minLabel > d[node].first) {
                        l--;
                    }
                    content[l].content.push_back(node);
                    d[node].second = content[l].content.end();
                    content[l].elements += 1;
                }
            }
        }
        auto edges = g->getEdges(u);

        for (auto& e : edges) {
            if (d[e.dest].first > d[u].first + e.w) {
                if (d[e.dest].first != INF) {
                    int j = 0;
                    while (content[j].maxLabel < d[e.dest].first) {
                        j++;
                    }
                    content[j].content.remove(e.dest);
                    content[j].elements--;
                }

                d[e.dest].first = d[u].first + e.w;
                pred[e.dest] = u;
                int j = 0;
                while (content[j].maxLabel < d[e.dest].first) {
                    j++;
                }
                content[j].content.push_front(e.dest);
                content[j].elements++;

                d[e.dest].second = content[j].content.begin();
            }
        }
    }
    return d[goal].first;
}

