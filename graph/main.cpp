#include <iostream>
#include <fstream>
#include "data_structure/include/graph.hpp"
#include "algorithms/include/connected.hpp"
#include "algorithms/include/minimum_spanning_tree.hpp"

int main() {
    // Open the input file
    std::ifstream file("data/input/graph_weighted.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open graph_weighted.txt" << std::endl;
        return 1;
    }

    // Read number of vertices and edges
    int numVertices, numEdges;
    file >> numVertices >> numEdges;

    // Create graph with the specified number of vertices and set it as weighted
    Graph graph(numVertices, true);

    // Read vertices (though we don't need to do anything with them since they're already created)
    for (int i = 0; i < numVertices; i++) {
        int vertex;
        file >> vertex;
    }

    // Read and add edges with weights
    for (int i = 0; i < numEdges; i++) {
        int u, v, weight;
        file >> u >> v >> weight;
        graph.addEdge(u, v, weight);
    }

    // Close the file
    file.close();

    // Print the graph
    std::cout << "Graph Structure:" << std::endl;
    graph.printGraph();

    if(is_connected(graph))
    {
        std::cout << "O grafo e conexo" << std::endl;
    }
    else
    {
        std::cout << "O grafo nao e conexo" << std::endl;
    }

    std::cout << "O numero de componentes conexos e: " << connected_component_amount(graph) << std::endl;
    std::cout << "O numero de vertices no componente conexo de 6 e: " << vertices_amount_in_connected_component(graph, 6) << std::endl;
    std::cout << "O grafo e " << 1 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 1) ? "SIM" : "NAO") << std::endl;
    std::cout << "O grafo e " << 2 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 2) ? "SIM" : "NAO") << std::endl;
    std::cout << "O grafo e " << 3 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 3) ? "SIM" : "NAO") << std::endl;
    std::cout << "O grafo e " << 4 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 4) ? "SIM" : "NAO") << std::endl;
    std::cout << "O grafo e " << 5 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 5) ? "SIM" : "NAO") << std::endl;
    std::cout << "O grafo e " << 6 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 6) ? "SIM" : "NAO") << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "O grafo e " << 1 << "-vertice-conexo?: " << (is_k_vertex_connected(graph, 1) ? "SIM" : "NAO") << std::endl;
    std::cout << "O grafo e " << 2 << "-vertice-conexo?: " << (is_k_vertex_connected(graph, 2) ? "SIM" : "NAO") << std::endl;
    std::cout << "O grafo e " << 3 << "-vertice-conexo?: " << (is_k_vertex_connected(graph, 3) ? "SIM" : "NAO") << std::endl;
    std::cout << "O grafo e " << 4 << "-vertice-conexo?: " << (is_k_vertex_connected(graph, 4) ? "SIM" : "NAO") << std::endl;
    std::cout << "O grafo e " << 5 << "-vertice-conexo?: " << (is_k_vertex_connected(graph, 5) ? "SIM" : "NAO") << std::endl;
    std::cout << "O grafo e " << 6 << "-vertice-conexo?: " << (is_k_vertex_connected(graph, 6) ? "SIM" : "NAO") << std::endl;
    std::cout << "O grafo e uma floresta?: " << (is_forest(graph) ? "SIM" : "NAO") << std::endl;
    
    std::vector<Edge> mst = kruskal_mst(graph);
    print_mst(mst);

    return 0;
}