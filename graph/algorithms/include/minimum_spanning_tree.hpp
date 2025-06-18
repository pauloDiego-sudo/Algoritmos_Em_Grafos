#ifndef MINIMUM_SPANNING_TREE_HPP
#define MINIMUM_SPANNING_TREE_HPP

#include <vector>
#include "../../data_structure/include/graph.hpp"
#include <limits.h>

#define INF INT_MAX

using namespace std;

/**
 * @brief Structure to represent an edge in the graph
 */
struct Edge {
    int u;      // First vertex
    int v;      // Second vertex
    int weight; // Weight of the edge

    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// Union-Find (Disjoint Set Union)
class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) : parent(n + 1), rank(n + 1, 0) {
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        if (rank[rx] < rank[ry]) parent[rx] = ry;
        else {
            parent[ry] = rx;
            if (rank[rx] == rank[ry]) rank[rx]++;
        }
    }
};

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
