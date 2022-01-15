#include <iostream>
#include "GraphAlgorithms.h"
#include "JuMPGenerator.h"

int main(int argc, char* argv[]) {
    auto g = GraphAlgorithms::generateHypercube<6>();
    g->print();
    JuMPGenerator::generateModelFile(*g, "hello.jl");
    // 10 1023
    // 14 16383
    // 16 65535
    //GraphAlgorithms::shortestAugmentingPath(*g, 0, 65535);
    //GraphAlgorithms::edmondsKarp(*g, 0, 1023);

    Graph h(true, g->getNumberOfVertices());
    for (int i = 0; i < g->getNumberOfVertices(); i++) {

        auto edges = g->getEdges(i);
        for (auto &e: edges) {
           h.addEdge(e->source, e->dest, e->u, 0);
        }
    }
    std::cout << "let's go\n";
    GraphAlgorithms::shortestAugmentingPath(*g, 0, 63);
    GraphAlgorithms::edmondsKarp(h, 0, 63);

    delete g;
    return 0;
}