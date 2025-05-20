#include <iostream>
#include <fstream>
#include "data_structure/include/graph.hpp"
#include "algorithms/include/connected.hpp"

int main() {
    // Open the input file
    std::ifstream file("data/graph_conex.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open graph.txt" << std::endl;
        return 1;
    }

    // Read number of vertices and edges
    int numVertices, numEdges;
    file >> numVertices >> numEdges;

    // Create graph with the specified number of vertices
    Graph graph(numVertices);

    // Read vertices (though we don't need to do anything with them since they're already created)
    for (int i = 0; i < numVertices; i++) {
        int vertex;
        file >> vertex;
    }

    // Read and add edges
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        file >> u >> v;
        graph.addEdge(u, v);
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
    std::cout << "O numero de vertices no componente conexo de 9 e: " << vertices_amount_in_connected_component(graph, 9) << std::endl;
    std::cout << "O grafo e " << 1 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 1) ? "SIM" : "NAO") << std::endl;
    std::cout << "O grafo e " << 2 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 2) ? "SIM" : "NAO") << std::endl;
    std::cout << "O grafo e " << 3 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 3) ? "SIM" : "NAO") << std::endl;

    return 0;
}

