#include "graph.hpp"

// copy-constructor: clona todas as listas
Graph::Graph(const Graph &other)
  : numVertices(other.numVertices),
    numEdges(other.numEdges),
    maxDegree(other.maxDegree),
    minDegree(other.minDegree),
    isWeighted(other.isWeighted),
    adjacencyList(other.numVertices + 1, nullptr)
{
    // Para cada vértice, percorre a lista original e vai clonando nó a nó
    for (int u = 1; u <= numVertices; ++u) {
        auto src = other.adjacencyList[u];
        // ponteiro para inserir em adjacencyList[u]
        std::shared_ptr<Node>* dstPtr = &adjacencyList[u];

        while (src) {
            // cria um novo Node com o mesmo valor e peso
            *dstPtr = std::make_shared<Node>(src->vertex, src->weight);
            // avança o ponteiro de destino para o próximo campo next
            dstPtr = &((*dstPtr)->next);
            // avança no fonte
            src = src->next;
        }
    }
}

/**
 * @brief Calculate the degree of a vertex
 * @param vertex The vertex to calculate degree for
 * @return The degree of the vertex
 */
int Graph::calculateDegree(int vertex) const
{
    int degree = 0;
    auto current = adjacencyList[vertex];
    while (current != nullptr)
    {
        degree++;
        current = current->next;
    }
    return degree;
}

/**
 * @brief Update max and min degrees after adding an edge
 */
void Graph::updateDegrees()
{
    maxDegree = 0;
    minDegree = numVertices; // Initialize with maximum possible value

    for (int i = 1; i <= numVertices; i++)
    {
        int degree = calculateDegree(i);
        maxDegree = std::max(maxDegree, degree);
        minDegree = std::min(minDegree, degree);
    }
}

/**
 * @brief Constructor for the Graph class
 * @param vertices Number of vertices in the graph
 * @param weighted Whether the graph is weighted
 */
Graph::Graph(int vertices, bool weighted) : numVertices(vertices), numEdges(0), maxDegree(0), minDegree(0), isWeighted(weighted)
{
    // Initialize adjacency list with nullptr for each vertex
    adjacencyList.resize(vertices + 1, nullptr);
}

/**
 * @brief Add a new isolated vertex to the graph
 * @return The index of the new vertex
 */
int Graph::addVertex()
{
    numVertices++;
    adjacencyList.push_back(nullptr);
    updateDegrees();
    return numVertices;
}

/**
 * @brief Add an edge to the graph
 * @param u First vertex
 * @param v Second vertex
 * @param weight Weight of the edge (default is 1)
 */
void Graph::addEdge(int u, int v, int weight)
{
    // Check if vertices exist
    if (u > numVertices || v > numVertices)
    {
        std::cout << "Error: Vertex out of range" << std::endl;
        return;
    }

    // If graph is not weighted, ignore weight value
    if (!isWeighted) {
        weight = 1;
    }

    // Add edge from u to v
    auto newNode = std::make_shared<Node>(v, weight);
    newNode->next = adjacencyList[u];
    adjacencyList[u] = newNode;

    // Add edge from v to u (undirected graph)
    newNode = std::make_shared<Node>(u, weight);
    newNode->next = adjacencyList[v];
    adjacencyList[v] = newNode;

    numEdges++;
    updateDegrees();
}

/**
 * @brief Get the order of the graph (number of vertices)
 * @return Number of vertices
 */
int Graph::getOrder() const
{
    return numVertices;
}

/**
 * @brief Get the size of the graph (number of edges)
 * @return Number of edges
 */
int Graph::getSize() const
{
    return numEdges;
}

/**
 * @brief Get the maximum degree of any vertex in the graph
 * @return Maximum degree
 */
int Graph::getMaxDegree() const
{
    return maxDegree;
}

/**
 * @brief Get the minimum degree of any vertex in the graph
 * @return Minimum degree
 */
int Graph::getMinDegree() const
{
    return minDegree;
}

/**
 * @brief Get the degree of a specific vertex
 * @param vertex The vertex to get the degree for
 * @return Degree of the vertex
 */
int Graph::getVertexDegree(int vertex) const
{
    return calculateDegree(vertex);
}

/**
 * @brief Get the adjacency list for a vertex
 * @param vertex The vertex to get the adjacency list for
 * @return Pointer to the first node in the adjacency list
 */
std::shared_ptr<Node> Graph::getAdjacencyList(int vertex) const
{
    return adjacencyList[vertex];
}

/**
 * @brief Print the graph structure and properties
 */
void Graph::printGraph() const
{
    std::cout << "Graph Properties:" << std::endl;
    std::cout << "Order (vertices): " << numVertices << std::endl;
    std::cout << "Size (edges): " << numEdges << std::endl;
    std::cout << "Maximum degree: " << maxDegree << std::endl;
    std::cout << "Minimum degree: " << minDegree << std::endl;
    std::cout << "Weighted: " << (isWeighted ? "Yes" : "No") << std::endl;
    std::cout << "\nAdjacency List:" << std::endl;

    for (int i = 1; i <= numVertices; i++)
    {
        std::cout << "Vertex " << i << " (degree " << calculateDegree(i) << ") -> ";
        auto current = adjacencyList[i];
        while (current != nullptr)
        {
            if (isWeighted) {
                std::cout << current->vertex << "(" << current->weight << ") ";
            } else {
                std::cout << current->vertex << " ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Remove an edge between two vertices
 * @param u First vertex
 * @param v Second vertex
 * @return true if edge was removed, false if edge didn't exist
 */
bool Graph::removeEdge(int u, int v)
{
    // Check if vertices exist
    if (u > numVertices || v > numVertices)
    {
        return false;
    }

    bool edgeRemoved = false;

    // Remove edge from u's adjacency list
    auto current = adjacencyList[u];
    std::shared_ptr<Node> prev = nullptr;
    while (current != nullptr)
    {
        if (current->vertex == v)
        {
            if (prev == nullptr)
            {
                adjacencyList[u] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            edgeRemoved = true;
            break;
        }
        prev = current;
        current = current->next;
    }

    // Remove edge from v's adjacency list
    current = adjacencyList[v];
    prev = nullptr;
    while (current != nullptr)
    {
        if (current->vertex == u)
        {
            if (prev == nullptr)
            {
                adjacencyList[v] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            break;
        }
        prev = current;
        current = current->next;
    }

    if (edgeRemoved)
    {
        numEdges--;
        updateDegrees();
    }

    return edgeRemoved;
}

/**
 * @brief Remove a vertex and all its incident edges
 * @param vertex The vertex to remove
 * @return true if vertex was removed, false if vertex didn't exist
 */
bool Graph::removeVertex(int v) {
    // 1) verifica existência
    if (v < 1 || v > numVertices) 
        return false;

    // 2) coleta vizinhos de v
    std::vector<int> neigh;
    for (auto curr = adjacencyList[v]; curr; curr = curr->next)
        neigh.push_back(curr->vertex);

    // 3) remove todas as arestas (v, w) usando removeEdge,
    //    que já ajusta numEdges e degrees corretamente
    for (int w : neigh) {
        removeEdge(v, w);
    }

    // 4) remove a própria linha de adjacência de v
    //    (shiftará automaticamente as posições > v)
    adjacencyList.erase(adjacencyList.begin() + v);

    // 5) decrementa o contador de vértices
    numVertices--;

    // 6) reindexa todos os nomes de vértices > v
    for (int u = 1; u <= numVertices; ++u) {
        for (auto curr = adjacencyList[u]; curr; curr = curr->next) {
            if (curr->vertex > v)
                --curr->vertex;
        }
    }

    // 7) finalmente, recalcula min/max degree
    updateDegrees();

    return true;
}

/**
 * @brief Check if the graph is weighted
 * @return true if graph is weighted, false otherwise
 */
bool Graph::getIsWeighted() const
{
    return isWeighted;
}

/**
 * @brief Set whether the graph is weighted
 * @param weighted Whether the graph should be weighted
 */
void Graph::setIsWeighted(bool weighted)
{
    isWeighted = weighted;
}

