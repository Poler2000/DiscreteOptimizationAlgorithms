#include <iostream>
#include "GraphFileReader.h"
#include "GraphAlgorithms.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Graph* g = GraphFileReader::loadGraph("../data/Long-n/Long-n.19.0.gr");
    g->print();
    auto results1 = GraphAlgorithms::dijkstra(g, 1);
    std::cout << "DIJKSTRA'S ALGORITHM:\n";
    /*for (auto& r: results) {
        std::cout << r << '\n';
    }*/
    std::cout << "DIAL'S ALGORITHM:\n";
    auto results2 = GraphAlgorithms::dial(g, 1, g->C);
    //std::cout << results1[1] << " ; " << results2[0] << '\n';
    //std::cout << results1[100] << " ; " << results2[99] << '\n';
    //std::cout << results1[10000] << " ; " << results2[9999] << '\n';
    //std::cout << results1[400001] << " ; " << results2[400000] << '\n';
    for (int i = 0; i < g->getNumberOfVertices(); i++) {
        if (results1[i + 1] != results2[i]) {
            //std::cout << "ALERT!";
            std::cout << results1[i+1] << " ; " << results2[i] << '\n';
        }
    }
    /*for (auto& r: results) {
        std::cout << r << '\n';
    }*/
    return 0;
}
