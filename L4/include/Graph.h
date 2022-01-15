//
// Created by pawel on 09.12.2021.
//

#ifndef L3_GRAPH_H
#define L3_GRAPH_H


#include <vector>
#include <memory>
#include <unordered_map>

struct Edge {
    int source;
    int dest;
    int u;
    int f;
    int w;
};

class Graph {
public:
    Graph(bool directed, int n);
    Graph(bool directed, int n, int m);
    void addEdge(int u, int v, int w = 1);
    void removeEdge(int u, int v);
    void addEdge(int u, int v, int uMax, int f = 0, int w = 1);
    int C = 0;
    //void removeEdge(int u, int v);

    void print() const;
    [[nodiscard]] std::vector<std::vector<int>> getAdjacencyList() const;
    [[nodiscard]] std::vector<int> getNeighbours(int n) const;
    [[nodiscard]] bool edgeExist(int u, int v);
    [[nodiscard]] std::shared_ptr<Edge> getEdge(int u, int v);
    [[nodiscard]] std::vector<std::shared_ptr<Edge>> getEdges(int s);
    int getNumberOfVertices() const;
    int getNumberOfEdges() const;
    bool isDirected() const;
private:
    bool _isDirected;
    int _n;
    int _m;
    std::unordered_map<int, std::vector<std::shared_ptr<Edge>>> _nodeMap;
    std::vector<std::vector<int>> _adjacencyList;
};


#endif //L3_GRAPH_H
