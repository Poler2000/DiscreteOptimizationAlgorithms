//
// Created by pawel on 09.12.2021.
//

#include <fstream>
#include "../include/GraphFileReader.h"

Graph *GraphFileReader::loadGraph(const std::string &path) {
    std::ifstream f(path, std::ios::in);
    if (!f.is_open()) {
        return nullptr;
    }
    char c;
    std::string s;
    int n = 0;
    int m = 0;
    Graph* g = nullptr;
    while (f.good()) {
        f >> c;
        switch (c) {
            case 'p':
                f >> s;
                f >> n;
                f >> m;
                g = new Graph(true, n, m);
                break;
            case 'a':
                if (g == nullptr) {
                    return nullptr;
                }
                int u, v, w;
                f >> u;
                f >> v;
                f >> w;
                g->addEdge(u, v, w);
                if (g->C < w) {
                    g->C = w;
                }
                break;
            case 'c':
                std::getline(f, s);
            default:
                break;
        }
    }
    return g;
}

std::vector<int> GraphFileReader::loadSources(const std::string &path) {
    std::vector<int> sources;
    std::ifstream f(path, std::ios::in);
    if (!f.is_open()) {
        return sources;
    }
    char c;
    std::string s;
    while (f.good()) {
        f >> c;
        switch (c) {
            case 's':
                int src;
                f >> src;
                sources.push_back(src);
                break;
            case 'p':
            case 'c':
                std::getline(f, s);
            default:
                break;
        }
    }
    return sources;
}

std::vector<std::pair<int, int>> GraphFileReader::loadPairs(const std::string &path) {
    std::vector<std::pair<int, int>> pairs;
    std::ifstream f(path, std::ios::in);
    if (!f.is_open()) {
        return pairs;
    }
    char c;
    std::string s;
    while (f.good()) {
        f >> c;
        switch (c) {
            case 'q':
                int p, q;
                f >> p;
                f >> q;
                pairs.emplace_back(std::make_pair(p, q));
                break;
            case 'p':
            case 'c':
                std::getline(f, s);
            default:
                break;
        }
    }
    return pairs;
}

void GraphFileReader::writeSSOutput(const std::string &path, const std::string& input1,
                                    const std::string& input2, Stats stats, double avgTime) {
    std::ofstream f(path, std::ios::out);
    if (!f.is_open()) {
        return;
    }
    f << "p res sp ss dijkstra\n";
    f << "f " << input1 << ' ' << input2 << '\n';
    f << "g " << stats.nodes << ' ' << stats.arcs << ' ';
    f << stats.minCost << ' ' << stats.maxCost << '\n';
    f << "t " << avgTime;
}

void GraphFileReader::writeP2POutput(const std::string &path, const std::string& input1,
                                     const std::string& input2, Stats stats, const std::vector<ShortestPath>& paths) {
    std::ofstream f(path, std::ios::out);
    if (!f.is_open()) {
        return;
    }
    f << "f " << input1 << ' ' << input2 << '\n';
    f << "g " << stats.nodes << ' ' << stats.arcs << ' ';
    f << stats.minCost << ' ' << stats.maxCost << '\n';
    for (auto& p: paths) {
        f << "d " << p.s << ' ' << p.d << ' ' << p.w << '\n';
    }
}
