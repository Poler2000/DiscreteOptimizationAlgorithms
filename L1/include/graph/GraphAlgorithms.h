//
// Created by Pawel Polerowicz
//
#ifndef AOD_GRAPHALGORITHMS_H
#define AOD_GRAPHALGORITHMS_H

#include "Result.h"
#include "Graph.h"

#include <set>

class GraphAlgorithms {
public:
    // Zad 1
    [[nodiscard]] static Result<Graph*> BFS(const Graph& graph, int s = 0);
    [[nodiscard]] static Result<Graph*> DFS(const Graph& graph, int s = 0);

    // Zad 2
    static Result<std::vector<int>> topologicalSort(const Graph& graph);

    // Zad 3
    static Result<std::vector<std::vector<int>>> stronglyConnectedComponents(const Graph& graph);

    // Zad 4
    static Result<std::pair<std::pair<std::set<int>, std::set<int>>, bool>> checkBigraph(const Graph& graph);

private:
    static void DFSHelper(const Graph& graph, Graph* tree, int s, std::vector<bool>& visited);
    static void topologicalDFS(const Graph& graph, std::vector<int>& visitedList);
    static void topologicalDFSHelper(const Graph& graph, std::vector<int>& visitedList, std::vector<bool>& visited, int s);
    static void sccDFSHelper(const Graph& graph, std::vector<bool>& visited, int s);

    static void
    checkBigraphDFSHelper(const Graph &graph, std::set<int>& green, std::set<int>& white, std::vector<bool>& visited,
                          int s, bool isGreen);
};

#endif //AOD_GRAPHALGORITHMS_H
