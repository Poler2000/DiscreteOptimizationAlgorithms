#include <iostream>
#include <fstream>
#include <cstring>
#include "GraphAlgorithms.h"
#include "JuMPGenerator.h"

void test() {
    std::ofstream f("results.txt", std::ios::out);
    if (!f.is_open()) {
        return;
    }
    for (int j = 1; j < 17; j++) {
        for (int k = 0; k < 10; k++) {
            auto g = GraphAlgorithms::generateHypercube(j);
            Graph h(true, g->getNumberOfVertices());
            for (int i = 0; i < g->getNumberOfVertices(); i++) {

                auto edges = g->getEdges(i);
                for (auto &e: edges) {
                    h.addEdge(e->source, e->dest, e->u, 0);
                }
            }
            f << j << ';';
            f << pow(2, j) << ';';
            auto result1 = GraphAlgorithms::edmondsKarp(h, 0, pow(2, j) - 1, false);
            auto result2 = GraphAlgorithms::shortestAugmentingPath(*g, 0, pow(2, j) - 1, false);
            f << result1.time << ';' << result2.time << ';';
            f << result1.paths << ';' << result2.paths << ';';
            f << result1.flow << ';' << result2.flow << '\n';

            delete g;
        }
    }
}


int main(int argc, char* argv[]) {
    //test();
    if (argc < 3) {
        std::cout << "use: ./L4 --size k [--printFlow]\n";
        exit(EXIT_SUCCESS);
    }
    int k = std::atoi(argv[2]);
    bool printFlow = false;
    if (argc == 4 && strcmp(argv[3], "--printFlow") == 0) {
        printFlow = true;
    }
    auto g = GraphAlgorithms::generateHypercube(k);
    g->print();
    JuMPGenerator::generateModelFile(*g, "hello.jl");
    Graph h(true, g->getNumberOfVertices());
    for (int i = 0; i < g->getNumberOfVertices(); i++) {

        auto edges = g->getEdges(i);
        for (auto &e: edges) {
            h.addEdge(e->source, e->dest, e->u, 0);
        }
    }
    int dest = pow(2, k) - 1;
    std::cout << "Edmonds-Karp:\n";
    auto result1 = GraphAlgorithms::edmondsKarp(*g, 0, dest, printFlow);
    std::cerr << "E-K time: " << result1.time << " paths: " << result1.paths << '\n';
    std::cout << "Shortest Augmenting Paths:\n";
    auto result2 = GraphAlgorithms::shortestAugmentingPath(h, 0, dest, printFlow);
    std::cerr << "SAP time: " << result2.time << " paths: " << result2.paths << '\n';

    return 0;
}