//
// Created by pawel on 09.12.2021.
//

#ifndef L3_GRAPHFILEREADER_H
#define L3_GRAPHFILEREADER_H


#include "Graph.h"
#include "Stats.h"
#include "ShortestPath.h"

class GraphFileReader {
public:
    static Graph* loadGraph(const std::string& path);
    static std::vector<int> loadSources(const std::string& path);
    static std::vector<std::pair<int, int>> loadPairs(const std::string& path);

    static void writeSSOutput(const std::string& path, const std::string& input1,
                              const std::string& input2, Stats stats, double avgTime);
    static void writeP2POutput(const std::string& path, const std::string& input1,
                               const std::string& input2, Stats stats, const std::vector<ShortestPath>& paths);
};


#endif //L3_GRAPHFILEREADER_H
