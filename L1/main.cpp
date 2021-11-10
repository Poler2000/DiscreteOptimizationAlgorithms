#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>

#include "./include/graph/GraphAlgorithms.h"

Graph* loadGraph(const std::string& inputFile) {
    int n, m, u, v;
    char directed;

    std::fstream f(inputFile, std::ios::in);
    if (f.bad()) {
        std::cout << "incorrect file\n";
        return nullptr;
    }

    // load graph data
    f >> directed;
    f >> n;
    f >> m;
    auto* g = new Graph(directed == 'D', n);
    for (int i = 0; i < m; i++) {
        f >> u;
        f >> v;
        g->addEdge(u, v);
    }
    f.close();
    return g;
}

void generateGraph(bool directed, int n, int m, const std::string& outputFile) {
    auto* g = new Graph(directed, n);
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<int> uid(0,n - 1);

    std::fstream f(outputFile, std::ios::out);
    if (f.bad()) {
        std::cout << "incorrect file\n";
        return;
    }

    f << (directed ? 'D' : 'U') << '\n';
    f << n << '\n';
    f << m << '\n';

    while (m > 0) {
        int a = uid(generator);
        int b = uid(generator);

        if (!g->edgeExist(a, b)) {
            g->addEdge(a, b);
            m--;
            f << a << ' ' << b << '\n';
        }
    }
    f.close();

    delete g;
}

int main(int argc, char* argv[]) {
    std::string inputFile(argv[1]);
    Graph* g = loadGraph(inputFile);

    std::cout << "graph:\n";
    g->print();

    std::cout<< "BFS:\n";
    auto result2 = GraphAlgorithms::BFS(*g);
    std::cout << "\nBFS tree:\n";
    result2.value->print();
    std::cout << "operation took: " << result2.time << "us\n";

    std::cout << "DFS:\n";
    auto result1 = GraphAlgorithms::DFS(*g);
    std::cout << "\nDFS tree:\n";
    result1.value->print();
    std::cout << "operation took: " << result1.time << "us\n";

    auto result3 = GraphAlgorithms::topologicalSort(*g);
    std::cout << "\nTopological tree:\n";
    for (auto& n : result3.value) {
        std::cout << n << " ";
    }
    std::cout << "operation took: " << result3.time << "us\n";

    std::cout << "\nSCC:\n";
    auto result4 = GraphAlgorithms::stronglyConnectedComponents(*g);
    std::cout << "operation took: " << result4.time << "us\n";

    std::cout << "\nBigraph:\n";
    auto result5 = GraphAlgorithms::checkBigraph(*g);
    std::cout << (result5.value.second ? "graph is a bigraph\n" : "graph is not a bigraph\n");
    std::cout << "operation took: " << result5.time << "us\n";

    return 0;
}
