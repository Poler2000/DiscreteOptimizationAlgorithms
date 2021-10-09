//
// Created by Pawel Polerowicz
//

#include "../../include/graph/Graph.h"

Graph::Graph(bool directed, int n)
    : _isDirected(directed) {
    _adjacencyList.resize(n);
}

Graph::Graph(bool directed, int n, int m)
    : _isDirected(directed) {
    _adjacencyList.resize(n);
}

void Graph::addEdge(int u, int v, int w) {
    if (!edgeExist(u, v)) {
        _adjacencyList[u].emplace_back(v);
    }
    if (!_isDirected) {
        if (!edgeExist(v, u)) {
            _adjacencyList[v].emplace_back(u);
        }
    }
}

void Graph::print() const {

}

std::vector<std::vector<int>> Graph::getAdjacencyList() const {
    return _adjacencyList;
}

std::vector<int> Graph::getNeighbours(int n) const {
    return _adjacencyList[n];
}

bool Graph::edgeExist(int u, int v) const {
    for (auto n : _adjacencyList[u]) {
        if (n == v) {
            return true;
        }
    }
    return false;
}
