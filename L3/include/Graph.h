//
// Created by pawel on 09.12.2021.
//

#ifndef L3_GRAPH_H
#define L3_GRAPH_H


#include <vector>
#include <unordered_map>

struct Edge {
    int source;
    int dest;
    int w;
};

class Graph {
public:
    Graph(bool directed, int n);
    Graph(bool directed, int n, int m);
    void addEdge(int u, int v, int w = 0);
    int C = 0;
    //void removeEdge(int u, int v);

    void print() const;
    [[nodiscard]] std::vector<std::vector<int>> getAdjacencyList() const;
    [[nodiscard]] std::vector<int> getNeighbours(int n) const;
    [[nodiscard]] bool edgeExist(int u, int v) const;
    [[nodiscard]] std::vector<Edge> getEdges(int s);
    int getNumberOfVertices() const;
    bool isDirected() const;
private:
    bool _isDirected;
    int _n;
    //std::vector<Edge> edges
    std::unordered_map<int, std::vector<Edge>> _nodeMap;
    std::vector<std::vector<int>> _adjacencyList;
};


#endif //L3_GRAPH_H
