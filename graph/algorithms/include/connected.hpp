#ifndef GRAPH_CONNECTED_HPP
#define GRAPH_CONNECTED_HPP

#include <vector>
#include <queue>
#include <unordered_set>
#include "../../data_structure/include/graph.hpp"

/**
 * @brief Checks if an undirected graph is connected using BFS
 * @param graph The graph to check
 * @return true if the graph is connected, false otherwise
 */
bool is_connected(const Graph& graph);

/**
 * @brief Returns the amount of vertices in the connected component of a given vertex
 * @param graph The graph to check
 * @param v The vertex to check
 * @return The amount of vertices in the connected component of v
 */
int vertices_amount_in_connected_component(const Graph& graph, int v);

/**
 * @brief Returns the amount of connected components in the graph
 * @param graph The graph to check
 * @return The amount of connected components in the graph
 */
int connected_component_amount(const Graph& graph);

/**
 * @brief Checks if an undirected graph is k-edge-connected
 * @param graph The graph to check
 * @param k The number of edges to remove
 * @return true if the graph is k-edge-connected, false otherwise
 */
bool is_k_edge_connected(Graph& graph, int k);

/**
 * @brief Checks if an undirected graph is k-vertex-connected
 * @param graph The graph to check
 * @param k The number of vertices to remove
 * @return true if the graph is k-vertex-connected, false otherwise
 */
bool is_k_vertex_connected(Graph& graph, int k);

/**
 * @brief Checks if an undirected graph is a forest
 * @param graph The graph to check
 * @return true if the graph is a forest, false otherwise (means it has cycles)
 */
bool is_forest(Graph& graph);

#endif // GRAPH_CONNECTED_HPP
