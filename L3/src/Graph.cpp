//
// Created by pawel on 09.12.2021.
//

#include "../include/Graph.h"

#include <iostream>

Graph::Graph(bool directed, int n)
        : _isDirected(directed), _n(n), _m(0) {
    _adjacencyList.resize(n + 1);
}

Graph::Graph(bool directed, int n, int m)
        : _isDirected(directed), _n(n), _m(0) {
    _adjacencyList.resize(n + 1);
}

void Graph::addEdge(int u, int v, int w) {
    if (!edgeExist(u, v)) {
        _adjacencyList[u].emplace_back(v);
        _nodeMap[u].emplace_back(Edge{u, v, w});
        _m++;
    }
    if (!_isDirected) {
        if (!edgeExist(v, u)) {
            _adjacencyList[v].emplace_back(u);
            _nodeMap[v].emplace_back(Edge{v, u, w});
        }
    }
}

void Graph::print() const {
    int i = 0;
    for (auto& v : _adjacencyList) {
        std::cout << i++ << ' ';
        for (auto n : v) {
            std::cout << n << ' ';
        }
        std::cout << '\n';
    }
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

int Graph::getNumberOfVertices() const {
    return _n;
}

bool Graph::isDirected() const {
    return _isDirected;
}

std::vector<Edge> Graph::getEdges(int s) {
    return _nodeMap[s];
}

int Graph::getNumberOfEdges() const {
    return _m;
}
