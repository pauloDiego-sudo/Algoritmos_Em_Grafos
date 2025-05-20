#include <iostream>
#include <vector>
#include <memory>

/**
 * @brief Node structure for the adjacency list
 */
struct Node {
    int vertex;    // The vertex that makes an edge with the vertex of its list index
    int cost;      // The cost of the edge
    std::shared_ptr<Node> next;  // Pointer to the next node in the list

    Node(int v, int c) : vertex(v), cost(c), next(nullptr) {}
};

/**
 * @brief Graph class using adjacency list representation
 */
class Graph {
private:
    std::vector<std::shared_ptr<Node>> adjacencyList;
    int numVertices;
    int numEdges;

public:
    /**
     * @brief Constructor for the Graph class
     * @param vertices Number of vertices in the graph
     */
    Graph(int vertices) : numVertices(vertices), numEdges(0) {
        // Initialize adjacency list with nullptr for each vertex
        adjacencyList.resize(vertices + 1, nullptr);
    }

    /**
     * @brief Add an edge to the graph
     * @param u First vertex
     * @param v Second vertex
     * @param cost Cost of the edge
     */
    void addEdge(int u, int v, int cost) {
        // Add edge from u to v
        auto newNode = std::make_shared<Node>(v, cost);
        newNode->next = adjacencyList[u];
        adjacencyList[u] = newNode;

        // Add edge from v to u (undirected graph)
        newNode = std::make_shared<Node>(u, cost);
        newNode->next = adjacencyList[v];
        adjacencyList[v] = newNode;

        numEdges++;
    }

    /**
     * @brief Get the number of vertices in the graph
     * @return Number of vertices
     */
    int getNumVertices() const {
        return numVertices;
    }

    /**
     * @brief Get the number of edges in the graph
     * @return Number of edges
     */
    int getNumEdges() const {
        return numEdges;
    }

    /**
     * @brief Get the adjacency list for a vertex
     * @param vertex The vertex to get the adjacency list for
     * @return Pointer to the first node in the adjacency list
     */
    std::shared_ptr<Node> getAdjacencyList(int vertex) const {
        return adjacencyList[vertex];
    }

    /**
     * @brief Print the graph structure
     */
    void printGraph() const {
        for (int i = 1; i <= numVertices; i++) {
            std::cout << "Vertex " << i << " -> ";
            auto current = adjacencyList[i];
            while (current != nullptr) {
                std::cout << "(" << current->vertex << ", " << current->cost << ") ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
};

// Example usage
int main() {
    // Create a graph with 5 vertices
    Graph graph(5);

    // Add some edges
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 4, 8);
    graph.addEdge(3, 4, 2);
    graph.addEdge(4, 5, 7);

    // Print the graph
    std::cout << "Graph Structure:" << std::endl;
    graph.printGraph();

    std::cout << "\nNumber of vertices: " << graph.getNumVertices() << std::endl;
    std::cout << "Number of edges: " << graph.getNumEdges() << std::endl;

    return 0;
} 