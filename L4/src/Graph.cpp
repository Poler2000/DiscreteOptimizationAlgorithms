//
// Created by pawel on 09.12.2021.
//

#include "../include/Graph.h"

#include <iostream>
#include <algorithm>

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
        _nodeMap[u].emplace_back(std::make_shared<Edge>(Edge{u, v, 0, 0, w}));
        _m++;
    }
    if (!_isDirected) {
        if (!edgeExist(v, u)) {
            _adjacencyList[v].emplace_back(u);
            _nodeMap[v].emplace_back(std::make_shared<Edge>(Edge{u, v, 0, 0, w}));
        }
    }
}

void Graph::addEdge(int u, int v, int uMax, int f, int w) {
    if (!edgeExist(u, v)) {
        _adjacencyList[u].emplace_back(v);
        _nodeMap[u].emplace_back(std::make_shared<Edge>(Edge{u, v, uMax, f, w}));
        _m++;
    }
    if (!_isDirected) {
        if (!edgeExist(v, u)) {
            _adjacencyList[v].emplace_back(u);
            _nodeMap[v].emplace_back(std::make_shared<Edge>(Edge{u, v, uMax, f, w}));
        }
    }
}

void Graph::removeEdge(int u, int v) {
    if (edgeExist(u, v)) {
        //std::cout << "before: " << _nodeMap[u].size() << '\n';
        auto e = getEdge(u, v);
        //std::cout << (std::find(_nodeMap[u].begin(), _nodeMap[u].end(), e) != _nodeMap[u].end());

        _nodeMap[u].erase(std::remove(_nodeMap[u].begin(), _nodeMap[u].end(), e));
        //std::cout << (std::find(_nodeMap[u].begin(), _nodeMap[u].end(), e) != _nodeMap[u].end());
        //std::cout << "after: " << _nodeMap[u].size() << '\n';
    }
}

void Graph::print() {
    /*int i = 0;
    for (auto& v : _adjacencyList) {
        std::cout << i++ << ' ';
        for (auto n : v) {
            std::cout << n << ' ';
        }
        std::cout << '\n';
    }*/
    for (int i = 0; i < _n; i++) {
        std::cout << i << ' ' << std::flush;
        for (auto n : _nodeMap[i]) {
            std::cout << "d: " << n->dest << " u: " << n->u << ' ';
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

bool Graph::edgeExist(int u, int v) {
    for (auto& n : _nodeMap[u]) {
        if (n->dest == v) {
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

std::vector<std::shared_ptr<Edge>> Graph::getEdges(int s) {
    return _nodeMap[s];
}

int Graph::getNumberOfEdges() const {
    return _m;
}

std::shared_ptr<Edge> Graph::getEdge(int u, int v) {
    for (auto& e: _nodeMap[u]) {
        if (e->dest == v) {
            return e;
        }
    }
    return nullptr;
}
