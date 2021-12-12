//
// Created by pawel on 09.12.2021.
//

#include "GraphAlgorithms.h"
#include "PriorityQueue.h"
#include "Timer.h"
#include "Bucket.h"

#include <list>

std::vector<long> GraphAlgorithms::dijkstra(Graph* g, int s) {
    Timer t;
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
        auto edges = g->getEdges(u);
        for (auto& e : edges) {
            if (d[e.dest] > d[u] + e.w) {
                d[e.dest] = d[u] + e.w;
                pred[e.dest] = u;
                q.priority(e.dest, d[e.dest]);
            }
        }
    }
    std::cout << "t0: " << t.getTimeInMicroseconds().count() << '\n';
    return d;
}

std::vector<long> GraphAlgorithms::dial(Graph *g, int s, int C) {
    Timer t1;
    size_t n = g->getNumberOfVertices();
    size_t nC = C + 1;
    int visited = 0;
    //std::vector<int> d(n + 1);
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
    //std::cout << "t1: " << t1.getTimeInMicroseconds().count() << '\n';
    Timer t2;
    while(visited < n) {
        Timer t3;
        while (content[i % nC].empty() && i < nC * n) {
            i++;
        }
        //std::cout << "t3: " << t3.getTimeInMicroseconds().count() << '\n';
        if (i >= nC * n) {
            break;
        }
        int u = content[i % nC].front();
        visited++;
        content[i % nC].pop_front();

        auto edges = g->getEdges(u);

        Timer t4;

        for (auto& e : edges) {
            if (d[e.dest].first > d[u].first + e.w) {
                Timer t5;
                if (d[e.dest].first != INF) {
                    //content[d[e.dest].first % nC].remove(e.dest);
                    content[d[e.dest].first % nC].erase(d[e.dest].second);
                }
                //std::cout << "t5: " << t5.getTimeInMicroseconds().count() << '\n';

                Timer t6;
                d[e.dest].first = d[u].first + e.w;
                pred[e.dest] = u;

                content[d[e.dest].first % nC].push_front(e.dest);
                d[e.dest].second = content[d[e.dest].first % nC].begin();
                //std::cout << "t6: " << t6.getTimeInMicroseconds().count() << '\n';
            }
        }
        //std::cout << "t4: " << t4.getTimeInMicroseconds().count() << '\n';

    }
    //std::cout << "t2: " << t2.getTimeInMicroseconds().count() << '\n';

    std::vector<long> distance(n);
    for (size_t i = 1; i < n + 1; i++) {
        distance[i - 1] = d[i].first;
    }
    std::cout << "t2: " << t2.getTimeInMicroseconds().count() << '\n';

    return distance;
}

std::vector<long> GraphAlgorithms::radix(Graph *g, int s, int C) {
    size_t n = g->getNumberOfVertices();
    size_t nC = C + 1;
    int visited = 0;
    std::vector<std::pair<long, std::list<int>::iterator>> d(nC);
    std::vector<int> pred(n + 1);
    size_t nofBuckets = (size_t)std::log2(n) + 1;
    std::vector<Bucket> content(nofBuckets);
    content[0].minLabel = 0;
    content[0].maxLabel = 0;
    for (size_t i = 0; i < nofBuckets - 1; i++) {
        content[i + 1].minLabel = pow(2, i);
        content[i + 1].maxLabel = pow(2, i + 1) - 1;
    }
    for (size_t i = 1; i < n + 1; i++) {
        d[i].first = INF;
    }
    d[s].first = 0;
    pred[s] = s;
    content[0].content[0].push_back(s);
    content[0].empty = false;
    long i = 0;
    while(visited < n) {
        while (content[i].empty && i < nofBuckets) {
            i++;
        }
        if (i >= nofBuckets) {
            break;
        }
        long minLabel = INF;
        long u;
        for (long j = content[i].minLabel; j <= content[i].maxLabel; j++) {
            if (!content[i].content[j].empty()) {
                minLabel = j;
                u = content[i].content[j].front();
                content[i].content[j].pop_front();
                visited++;
                break;
            }
        }
        for (auto& b: content) {
            b.minLabel += minLabel;
            b.maxLabel += minLabel;
        }
        for (int j = 1; j < nofBuckets; j++) {
            for (int k = 0; k < content[j].maxLabel - content[j].minLabel + 1; k++) {
                int l = j;
                auto& list = content[i].content[j];
                std::remove(content[i].content.begin(), content[i].content.end(), list);
                while (content[l].minLabel > d[list.front()].first) {
                    l--;
                }
                content[l].content[d[list.front()].first - minLabel] = list;
            }
        }

        auto edges = g->getEdges(u);

        /*for (auto& e : edges) {
            if (d[e.dest].first > d[u].first + e.w) {
                if (d[e.dest].first != INF) {
                    content[d[e.dest].first % nC].remove(e.dest);
                }

                d[e.dest].first = d[u].first + e.w;
                pred[e.dest] = u;

                content[d[e.dest].first % nC].push_front(e.dest);
            }
        }*/
    }

    std::vector<long> distance(n);
    for (size_t i = 1; i < n + 1; i++) {
        distance[i - 1] = d[i].first;
    }
    return distance;
}
/*
std::vector<int> GraphAlgorithms::dial(Graph *g, int s, int C) {
    size_t n = g->getNumberOfVertices();
    size_t nC = n * C + 1;
    std::vector<int> d(n + 1);
    std::vector<int> pred(n + 1);
    std::vector<std::list<int>> content(nC);
    for (size_t i = 1; i < n + 1; i++) {
        d[i] = INF;
    }
    d[s] = 0;
    pred[s] = s;
    content[0].push_back(s);
    int i = 0;
    while(true) {
        while (content[i].empty()) {
            i++;
        }
        if (i == nC) {
            break;
        }
        int u = content[i].front();
        content[i].pop_front();

        auto edges = g->getEdges(u);
        for (auto& e : edges) {
            if (d[e.dest] > d[u] + e.w) {
                if (d[e.dest] != INF) {
                    content[d[e.dest]].remove(e.dest);
                }
                d[e.dest] = d[u] + e.w;
                pred[e.dest] = u;

                content[d[e.dest]].push_front(e.dest);
            }
        }
    }
    return d;
}*/
/*
void Graph::djikstra(int s) {
    Timer t;
    std::unordered_map<int, double> dist;
    std::unordered_map<int, int> prev;

    for (auto& kv : nodeMap) {
        dist[kv.first] = INT32_MAX;
        prev[kv.first] = -1;
    }
    dist[s] = 0;

    PriorityQueue q;

    for (auto& kv : nodeMap) {
        q.insert(kv.first, dist[kv.first] * 100);
    }

    while(!q.empty()) {
        int u = q.pop();
        for (auto& n : nodeMap[u]) {
            if (dist[n.dest] > dist[u] + n.w) {
                dist[n.dest] = dist[u] + n.w;
                prev[n.dest] = u;
                q.priority(n.dest, dist[n.dest] * 100);
            }
        }
    }
    long time = t.getTimeInMicroseconds().count();
    for (int i = 0; i < dist.size(); i++) {
        std::cout << i << ' ' << dist[i] << '\n';
    }
    for (int i = 0; i < dist.size(); i++) {
        std::cerr << "Path to: "<< i << " is: ";
        int j = i;
        std::vector<double> path{};
        while (j != s) {
            auto vec = nodeMap[prev[j]];
            for (auto& n : vec) {
                if (n.dest == j) {
                    path.push_back(n.w);
                    break;
                }
            }
            path.push_back(prev[j]);

            j = prev[j];
        }
        std::reverse(path.begin(), path.end());
        for (auto& n : path) {
            std::cerr << n << ' ';
        }
        std::cerr << '\n';
    }
    std::cerr << "time: " << time << "us";
}*/