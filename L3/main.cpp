#include <iostream>
#include "include/Timer.h"
#include <string>
#include "include/GraphFileReader.h"
#include "include/GraphAlgorithms.h"

int main() {

    for (int j = 10; j < 22; j++) {
        std::string num = std::to_string(j);
        Graph* g = GraphFileReader::loadGraph("../data/Long-n/Long-n." + num + ".0.gr");
        auto sources = GraphFileReader::loadSources("../data/Long-n/Long-n." + num + ".0.ss");
        for (int i = 0; i < 1; i++) {
            std::cout << j << ';';
            Timer t1;
            auto results1 = GraphAlgorithms::dijkstra(g, sources[i]);
            std::cout << t1.getTimeInMicroseconds().count() << ';';
            Timer t2;
            auto results2 = GraphAlgorithms::dial(g, sources[i], g->C);
            std::cout << t2.getTimeInMicroseconds().count() << ';';
            Timer t3;
            auto results3 = GraphAlgorithms::radix(g, sources[i], g->C);
            std::cout << t3.getTimeInMicroseconds().count() << '\n';
        }
        delete g;
    }
/*
    Timer t1;
    std::cout << "DIJKSTRA'S ALGORITHM:\n";
    auto results1 = GraphAlgorithms::dijkstra(g, 1);
    std::cout << t1.getTimeInMicroseconds().count() << '\n';
    Timer t2;
    std::cout << "DIAL'S ALGORITHM:\n";
    auto results2 = GraphAlgorithms::dial(g, 1, g->C);
    std::cout << t2.getTimeInMicroseconds().count() << '\n';
    std::cout << "RADIX HEAP ALGORITHM:\n";
    Timer t3;
    auto results3 = GraphAlgorithms::radix(g, 1, g->C);
    std::cout << t3.getTimeInMicroseconds().count() << '\n';

    for (int i = 0; i < g->getNumberOfVertices(); i++) {
        if (results1[i + 1] != results2[i]) {
            std::cout << results1[i+1] << " ; " << results2[i] << '\n';
        }
        if (results1[i + 1] != results3[i]) {
            std::cout << results1[i+1] << " ; " << results2[i] << '\n';
        }
        if (results2[i] != results3[i]) {
            std::cout << results1[i+1] << " ; " << results2[i] << '\n';
        }
    }*/
    /*for (auto& r: results3) {
        std::cout << r << '\n';
    }*/
    return 0;
}
