//
// Created by pawel on 15.01.2022.
//

#include "JuMPGenerator.h"
#include <fstream>
#include <valarray>

void JuMPGenerator::generateModelFile(Graph &g, const std::string &filename) {
    std::ofstream f(filename, std::ios::out);
    if (!f.is_open()) {
        return;
    }
    f << "using JuMP\n";
    f << "using GLPK\n";
    f << '\n';
    f << "HyperCube = Dict(";
    for (int i = 0; i < g.getNumberOfVertices(); i++) {
        auto edges = g.getEdges(i);
        for (auto& e : edges) {
            f << "\t\"" << e->source << ' ' << e->dest << "\" => " << e->u << ",\n";
        }
    }
    f << "\t)";
    f << '\n';
    f << "n = " << g.getNumberOfVertices() << '\n';
    f << "max_flow = Model(GLPK.Optimizer)\n";
    f << '\n';
    f << "@variable(max_flow, f[1:n, 1:n] >= 0)\n";
    f << '\n';
    f << "@constraint(max_flow, [i = 0:n-1, j = 0:n-1], f[i+1, j+1] <= get(HyperCube, \"$i $j\", 0))\n";
    f << '\n';
    f << "@constraint(max_flow, [i = 1:n; i != 1 && i != "
      << g.getNumberOfVertices() << "], sum(f[i, :]) == sum(f[:, i]))\n";

    f << "@objective(max_flow, Max, sum(f[1, :]))\n";

    f << "optimize!(max_flow)\n"
         "objective_value(max_flow)\n"
         "\n"
         "println(objective_value(max_flow))\n"
         "\n"
         "println(value.(f))";
    f.close();
}
