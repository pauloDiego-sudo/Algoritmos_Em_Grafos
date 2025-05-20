#include "minimum_spanning_tree.hpp"
#include "connected.hpp"
#include <algorithm>
#include <vector>

//print the mst
void print_mst(const std::vector<Edge>& mst) {
    for (const Edge& edge : mst) {
        std::cout << edge.u << " " << edge.v << " " << edge.weight << std::endl;
    }
}

/**
 Algoritmo de Kruskal
 ENTRADA: Um grafo G com n vertices e m arestas, onde cada aresta tem um custo
 SAIDA: Um conjunto de arestas T tal que G[T] é uma arvore geradora minima de G

 T = {}
 i = 1
 COLOQUE AS ARESTAS DE G EM ORDEM CRESCENTE DE CUSTO
 ENQUANTO |T| < n-1:
    SE G[T U {aresta_i}] FOR ACICLICO
        T = T U {aresta_i}
    i++
DEVOLVA T
 */
std::vector<Edge> kruskal_mst(const Graph& graph) {
    int n = graph.getOrder();
    std::vector<Edge> T;  // MST edges
    std::vector<Edge> edges;
    
    // Collect all edges from the graph
    for (int u = 1; u <= n; ++u) {
        auto current = graph.getAdjacencyList(u);
        while (current != nullptr) {
            // Only add each edge once (u < v to avoid duplicates)
            if (u < current->vertex) {
                edges.emplace_back(u, current->vertex, current->weight);
            }
            current = current->next;
        }
    }
    
    // Sort edges by weight (COLOQUE AS ARESTAS DE G EM ORDEM CRESCENTE DE CUSTO)
    std::sort(edges.begin(), edges.end(), 
        [](const Edge& a, const Edge& b) { return a.weight < b.weight; });
    
    // Create a temporary graph to check for cycles
    Graph temp_graph(n, true);  // true for weighted graph
    
    // Process edges until we have n-1 edges in the MST
    for (const Edge& edge : edges) {
        // ENQUANTO |T| < n-1
        if (T.size() >= n - 1) break;
        
        // Add the edge to the temporary graph
        temp_graph.addEdge(edge.u, edge.v, edge.weight);
        
        // SE G[T U {aresta_i}] FOR ACICLICO
        if (is_forest(temp_graph)) {
            // T = T U {aresta_i}
            T.push_back(edge);
        } else {
            // Remove the edge if it creates a cycle
            temp_graph.removeEdge(edge.u, edge.v);
        }
    }
    
    return T;
}
