//
// Created by Pawel Polerowicz
//

#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <set>

#include "../../include/graph/GraphAlgorithms.h"

Result<Graph*> GraphAlgorithms::BFS(const Graph &graph, int s) {
    std::vector<bool> visited(graph.getNumberOfVertices());
    auto tree = new Graph(true, graph.getNumberOfVertices());
    Timer t;

    for (int i = 0; i < graph.getNumberOfVertices(); i++) {
        visited[i] = false;
    }

    std::queue<int> queue;

    visited[s] = true;
    queue.push(s);

    while(!queue.empty()) {
        s = queue.front();
        std::cout << s << " ";
        queue.pop();

        auto neighbours = graph.getNeighbours(s);
        for (auto n : neighbours) {
            if (!visited[n]) {
                visited[n] = true;
                queue.push(n);
                tree->addEdge(s, n);
            }
        }
    }
    Result<Graph*> r = {tree, t.getTimeInMicroseconds(), 0};
    return r;
}

Result<Graph*> GraphAlgorithms::DFS(const Graph &graph, int s) {
    std::vector<bool> visited(graph.getNumberOfVertices());
    auto tree = new Graph(true, graph.getNumberOfVertices());
    Timer t;

    for (int i = 0; i < graph.getNumberOfVertices(); i++) {
        visited[i] = false;
    }

    for (int i = 0; i < graph.getNumberOfVertices(); i++) {
        if (!visited[i]) {
            DFSHelper(graph, tree, s, visited);
        }
    }
    Result<Graph*> r = {tree, t.getTimeInMicroseconds(), 0};
    return r;
}

void GraphAlgorithms::DFSHelper(const Graph &graph, Graph* tree, int s, std::vector<bool>& visited) {
    visited[s] = true;
    std::cout << s << " ";

    auto neighbours = graph.getNeighbours(s);
    for (auto n : neighbours) {
        if (!visited[n]) {
            tree->addEdge(s, n);
            DFSHelper(graph, tree, n, visited);
        }
    }
}

Result<std::vector<int>> GraphAlgorithms::topologicalSort(const Graph &graph) {
    Timer t;
    std::vector<int> visitedList;

    topologicalDFS(graph, visitedList);
    std::reverse(visitedList.begin(), visitedList.end());

    return Result<std::vector<int>>{visitedList, t.getTimeInMicroseconds(), 0};
}

void GraphAlgorithms::topologicalDFS(const Graph &graph, std::vector<int> &visitedList) {
    std::vector<bool> visited(graph.getNumberOfVertices());
    Timer t;

    for (int i = 0; i < graph.getNumberOfVertices(); i++) {
        visited[i] = false;
    }

    for (int i = 0; i < graph.getNumberOfVertices(); i++) {
        if (!visited[i]) {
            topologicalDFSHelper(graph, visitedList, visited, 0);
        }
    }
}

void
GraphAlgorithms::topologicalDFSHelper(const Graph &graph, std::vector<int> &visitedList, std::vector<bool> &visited, int s) {
    visited[s] = true;

    auto neighbours = graph.getNeighbours(s);
    for (auto n : neighbours) {
        if (!visited[n]) {
            topologicalDFSHelper(graph, visitedList, visited, n);
        }
    }
    visitedList.emplace_back(s);
}

Result<std::vector<std::vector<int>>> GraphAlgorithms::stronglyConnectedComponents(const Graph &graph) {
    Timer t;
    std::vector<int> visitedList;
    Graph g(graph.isDirected(), graph.getNumberOfVertices());

    topologicalDFS(graph, visitedList);
    for (int i = 0; i < graph.getNumberOfVertices(); i++) {
        for (auto n : graph.getNeighbours(i)) {
            g.addEdge(n, i);
        }
    }

    std::vector<bool> visited(g.getNumberOfVertices());

    for (int i = 0; i < g.getNumberOfVertices(); i++) {
        visited[i] = false;
    }
    std::reverse(visitedList.begin(), visitedList.end());


    for (auto& n: visitedList) {
        if (!visited[n]) {
            sccDFSHelper(g, visited, n);
            std::cout << '\n';
        }
    }
}

void GraphAlgorithms::sccDFSHelper(const Graph &graph, std::vector<bool> &visited, int s) {
    visited[s] = true;
    std::cout << s << " ";
    auto neighbours = graph.getNeighbours(s);
    for (auto n : neighbours) {
        if (!visited[n]) {
            sccDFSHelper(graph, visited, n);
        }
    }
}

Result<std::pair<std::pair<std::set<int>, std::set<int>>, bool>> GraphAlgorithms::checkBigraph(const Graph &graph) {
    std::set<int> green;
    std::set<int> white;

    std::vector<bool> visited(graph.getNumberOfVertices());
    Timer t;

    for (int i = 0; i < graph.getNumberOfVertices(); i++) {
        visited[i] = false;
    }

    for (int i = 0; i < graph.getNumberOfVertices(); i++) {
        if (!visited[i]) {
            checkBigraphDFSHelper(graph, green, white, visited, i, true);
        }
    }
    std::vector<int>intersection;
    std::set_intersection(green.begin(), green.end(), white.begin(), white.end(), std::back_inserter(intersection));
    return Result<std::pair<std::pair<std::set<int>, std::set<int>>, bool>>
        {std::make_pair(std::make_pair(green, white), intersection.empty()), t.getTimeInMicroseconds(), 0};
}

void GraphAlgorithms::checkBigraphDFSHelper(const Graph &graph, std::set<int>& green, std::set<int>& white,
                                            std::vector<bool>& visited, int s, bool isGreen) {
    if (isGreen) {
        green.insert(s);
    }
    else {
        white.insert(s);
    }

    visited[s] = true;
    auto neighbours = graph.getNeighbours(s);
    for (auto n : neighbours) {
        if (isGreen) {
            white.insert(n);
        }
        else {
            green.insert(n);
        }
        if (!visited[n]) {
            checkBigraphDFSHelper(graph, green, white, visited, n, !isGreen);
        }
    }
}
