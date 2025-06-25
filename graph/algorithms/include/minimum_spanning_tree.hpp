#ifndef MINIMUM_SPANNING_TREE_HPP
#define MINIMUM_SPANNING_TREE_HPP

#include <vector>
#include "../../data_structure/include/graph.hpp"
#include <limits.h>
#include "myDS.hpp"

#define INF INT_MAX

using namespace MyDataStructures;


//print the mst
void print_mst(const std::vector<Edge>& mst);

/**
 * @brief Finds the minimum spanning tree of a graph using Kruskal's algorithm
 * @param graph The input graph
 * @return A vector of edges representing the minimum spanning tree
 */
vector<Edge> kruskal_mst_naive(const Graph& graph);

/**
 * @brief Finds the minimum spanning tree of a graph using Kruskal's algorithm
 * @param graph The input graph
 * @return A vector of edges representing the minimum spanning tree
 */
vector<Edge> kruskal_mst_paint(const Graph& graph);

/**
 * @brief Finds the minimum spanning tree of a graph using Kruskal's algorithm
 * @param graph The input graph
 * @return A vector of edges representing the minimum spanning tree
 */
vector<Edge> kruskal_mst(const Graph& graph);

/**
 * @brief Finds the minimum spanning tree of a graph using Prim's algorithm
 * @param graph The input graph
 * @return A vector of edges representing the minimum spanning tree
 */
vector<Edge> prim_mst_naive(const Graph& graph);

/**
 * @brief Finds the minimum spanning tree of a graph using Prim's algorithm
 * @param graph The input graph
 * @return A vector of edges representing the minimum spanning tree
 */
vector<Edge> prim_mst(const Graph& graph);

#endif // MINIMUM_SPANNING_TREE_HPP
