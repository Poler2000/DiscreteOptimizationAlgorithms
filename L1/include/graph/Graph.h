//
// Created by Pawel Polerowicz
//

#ifndef AOD_GRAPH_H
#define AOD_GRAPH_H

#include <vector>

struct Edge {
    int u;
    int v;
    int w;
};

class Graph {
public:
    Graph(bool directed, int n);
    Graph(bool directed, int n, int m);
    void addEdge(int u, int v, int w = 0);
    //void removeEdge(int u, int v);

    void print() const;
    [[nodiscard]] std::vector<std::vector<int>> getAdjacencyList() const;
    [[nodiscard]] std::vector<int> getNeighbours(int n) const;
    [[nodiscard]] bool edgeExist(int u, int v) const;
    int getNumberOfVertices() const;
    bool isDirected() const;
private:
    bool _isDirected;
    int _n;
    //std::vector<Edge> edges
    std::vector<std::vector<int>> _adjacencyList;
};


#endif //AOD_GRAPH_H
