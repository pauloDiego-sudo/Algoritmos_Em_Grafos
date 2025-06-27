#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <queue>
#include <algorithm>
#include "graph.hpp"
#include "myDS.hpp"

using namespace MyDataStructures;

/** @brief Performs a breadth-first search (BFS) on the graph starting from a given vertex.
 * @param graph The graph to traverse.
 * @param vertice The starting vertex for the BFS.
 * @param visited A vector to keep track of visited vertices.
 */
void bfs(const Graph &graph, int vertice, vector<bool> &visited);

/** @brief Performs a depth-first search (DFS) on the graph starting from a given vertex.
 * @param graph The graph to traverse.
 * @param vertice The starting vertex for the DFS.
 * @param visited A vector to keep track of visited vertices.
 */
void dfs(const Graph &graph, int vertice, vector<bool> &visited);

/** @brief Checks if an edge (u, v) is a bridge in the graph.
 * A bridge is an edge whose removal increases the number of connected components in the graph.
 * @param graph The graph to check.
 * @param u The first vertex of the edge.
 * @param v The second vertex of the edge.
 * @return true if the edge (u, v) is a bridge, false otherwise.
 */
bool isBridge(Graph &graph, int u, int v);



#endif // UTILS_HPP