#include <iostream>
#include <fstream>
#include "data_structure/include/graph.hpp"
#include "algorithms/include/connected.hpp"
#include "algorithms/include/minimum_spanning_tree.hpp"

int main() {
    // Open the input file
    ifstream file("data/input/graph_weighted.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open graph_weighted.txt" << endl;
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
    cout << "Graph Structure:" << endl;
    graph.printGraph();

    if(is_connected(graph))
    {
        cout << "O grafo e conexo" << endl;
    }
    else
    {
        cout << "O grafo nao e conexo" << endl;
    }

    cout << "O numero de componentes conexos e: " << connected_component_amount(graph) << endl;
    cout << "O numero de vertices no componente conexo de 6 e: " << vertices_amount_in_connected_component(graph, 6) << endl;
    cout << "O grafo e " << 1 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 1) ? "SIM" : "NAO") << endl;
    cout << "O grafo e " << 2 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 2) ? "SIM" : "NAO") << endl;
    cout << "O grafo e " << 3 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 3) ? "SIM" : "NAO") << endl;
    cout << "O grafo e " << 4 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 4) ? "SIM" : "NAO") << endl;
    cout << "O grafo e " << 5 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 5) ? "SIM" : "NAO") << endl;
    cout << "O grafo e " << 6 << "-aresta-conexo?: " << (is_k_edge_connected(graph, 6) ? "SIM" : "NAO") << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "O grafo e " << 1 << "-vertice-conexo?: " << (is_k_vertex_connected(graph, 1) ? "SIM" : "NAO") << endl;
    cout << "O grafo e " << 2 << "-vertice-conexo?: " << (is_k_vertex_connected(graph, 2) ? "SIM" : "NAO") << endl;
    cout << "O grafo e " << 3 << "-vertice-conexo?: " << (is_k_vertex_connected(graph, 3) ? "SIM" : "NAO") << endl;
    cout << "O grafo e " << 4 << "-vertice-conexo?: " << (is_k_vertex_connected(graph, 4) ? "SIM" : "NAO") << endl;
    cout << "O grafo e " << 5 << "-vertice-conexo?: " << (is_k_vertex_connected(graph, 5) ? "SIM" : "NAO") << endl;
    cout << "O grafo e " << 6 << "-vertice-conexo?: " << (is_k_vertex_connected(graph, 6) ? "SIM" : "NAO") << endl;
    cout << "O grafo e uma floresta?: " << (is_forest(graph) ? "SIM" : "NAO") << endl;
    
    vector<Edge> mst_union_find = kruskal_mst(graph);
    print_mst(mst_union_find);
    cout << "-------------------------------------------------------" << endl;

    vector<Edge> mst_prim_naive = prim_mst_naive(graph);
    print_mst(mst_prim_naive);
    cout << "-------------------------------------------------------" << endl;
    return 0;
}