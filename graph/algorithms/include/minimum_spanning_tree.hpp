#ifndef MINIMUM_SPANNING_TREE_HPP
#define MINIMUM_SPANNING_TREE_HPP

#include <vector>
#include "../../data_structure/include/graph.hpp"

/**
 * @brief Structure to represent an edge in the graph
 */
struct Edge {
    int u;      // First vertex
    int v;      // Second vertex
    int weight; // Weight of the edge

    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

//print the mst
void print_mst(const std::vector<Edge>& mst);

/**
 * @brief Finds the minimum spanning tree of a graph using Kruskal's algorithm
 * @param graph The input graph
 * @return A vector of edges representing the minimum spanning tree
 */
std::vector<Edge> kruskal_mst(const Graph& graph);

#endif // MINIMUM_SPANNING_TREE_HPP
