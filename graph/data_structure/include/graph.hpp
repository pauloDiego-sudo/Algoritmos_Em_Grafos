#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

/**
 * @brief Node structure for the adjacency list
 */
struct Node {
    int vertex;    // The vertex that makes an edge with the vertex of its list index
    std::shared_ptr<Node> next;  // Pointer to the next node in the list

    Node(int v) : vertex(v), next(nullptr) {}
};

/**
 * @brief Graph class using adjacency list representation
 */
class Graph {
private:
    std::vector<std::shared_ptr<Node>> adjacencyList;
    int numVertices;    // Order of the graph
    int numEdges;       // Size of the graph
    int maxDegree;      // Maximum degree of any vertex
    int minDegree;      // Minimum degree of any vertex

    /**
     * @brief Calculate the degree of a vertex
     * @param vertex The vertex to calculate degree for
     * @return The degree of the vertex
     */
    int calculateDegree(int vertex) const;

    /**
     * @brief Update max and min degrees after adding an edge
     */
    void updateDegrees();

public:
    /**
     * @brief Constructor for the Graph class
     * @param vertices Number of vertices in the graph
     */
    Graph(int vertices = 0);

    /**
     * @brief Add a new isolated vertex to the graph
     * @return The index of the new vertex
     */
    int addVertex();

    /**
     * @brief Add an edge to the graph
     * @param u First vertex
     * @param v Second vertex
     */
    void addEdge(int u, int v);

    /**
     * @brief Get the order of the graph (number of vertices)
     * @return Number of vertices
     */
    int getOrder() const;

    /**
     * @brief Get the size of the graph (number of edges)
     * @return Number of edges
     */
    int getSize() const;

    /**
     * @brief Get the maximum degree of any vertex in the graph
     * @return Maximum degree
     */
    int getMaxDegree() const;

    /**
     * @brief Get the minimum degree of any vertex in the graph
     * @return Minimum degree
     */
    int getMinDegree() const;

    /**
     * @brief Get the degree of a specific vertex
     * @param vertex The vertex to get the degree for
     * @return Degree of the vertex
     */
    int getVertexDegree(int vertex) const;

    /**
     * @brief Get the adjacency list for a vertex
     * @param vertex The vertex to get the adjacency list for
     * @return Pointer to the first node in the adjacency list
     */
    std::shared_ptr<Node> getAdjacencyList(int vertex) const;

    /**
     * @brief Remove an edge between two vertices
     * @param u First vertex
     * @param v Second vertex
     * @return true if edge was removed, false if edge didn't exist
     */
    bool removeEdge(int u, int v);

    /**
     * @brief Remove a vertex and all its incident edges
     * @param vertex The vertex to remove
     * @return true if vertex was removed, false if vertex didn't exist
     */
    bool removeVertex(int vertex);

    /**
     * @brief Print the graph structure and properties
     */
    void printGraph() const;
};

#endif // GRAPH_HPP