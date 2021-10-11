#include <iostream>
#include <fstream>
#include <filesystem>

#include "./include/graph/GraphAlgorithms.h"

int main(int argc, char* argv[]) {
    std::cout << std::filesystem::current_path();
    int n, m, u, v;
    char directed;
    std::string inputFile(argv[1]);
    std::fstream f(inputFile, std::ios::in);
    if (f.bad()) {
        std::cout << "incorrect file\n";
        return 1;
    }
    f >> directed;
    f >> n;
    f >> m;
    Graph g(directed == 'D', n);
    for (int i = 0; i < m; i++) {
        f >> u;
        f >> v;
        std::cout << u << ' ' << v << "\n";

        g.addEdge(u, v);
    }
    f.close();

    std::cout << "graph:\n";
    g.print();
    auto result1 = GraphAlgorithms::DFS(g);
    std::cout << "\nDFS tree:\n";

    result1.value->print();
    auto result2 = GraphAlgorithms::BFS(g);
    std::cout << "\nBFS tree:\n";
    result2.value->print();

    /*auto result3 = GraphAlgorithms::topologicalSort(g);
    std::cout << "\nTopological tree:\n";
    for (auto& n : result3.value) {
        std::cout << n << " ";
    }*/
    std::cout << "\nSTC:\n";

    auto result4 = GraphAlgorithms::stronglyConnectedComponents(g);
    /*for (auto& n : result4.value) {
        for (auto k : n) {
            std::cout << k << " ";
        }
    }*/
    std::cout << "\nBigraph:\n";

    auto result5 = GraphAlgorithms::checkBigraph(g);
    std::cout << result5.value.second;

    return 0;
}
