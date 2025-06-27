#include "trails.hpp"


EulerianTrailProperties getEulerianPropetiesOfGraph(const Graph &graph)
{
    // An undirected graph is Eulerian if all vertices with nonzero degree have even degree, or if the graph has exactaly 2 vertices with odd degree
    // and all vertices with nonzero degree are connected.
    EulerianTrailProperties properties;
    int oddDegreeCount = 0;
    int n = graph.getOrder();
    int nonZeroDegreeVertex = -1;

    // Find a vertex with nonzero degree to start bfs
    for (int i = 0; i < n; ++i)
    {
        if (graph.getVertexDegree(i) > 0)
        {
            nonZeroDegreeVertex = i;
            break;
        }
    }
    if (nonZeroDegreeVertex == -1)
    {
        // No edges in the graph
        // return false;
        properties.isEulerian = false;
        return properties;
    }

    // Check all vertices have even degree
    for (int i = 0; i < n; ++i)
    {
        if (graph.getVertexDegree(i) % 2 != 0)
        {
            oddDegreeCount++;
            oddDegreeCount == 1 ? properties.startTAE = i : properties.endTAE = i;
        }
    }

    if (oddDegreeCount != 2 && oddDegreeCount != 0)
    {
        properties.isEulerian = false; // More than 2 vertices with odd degree
        // properties.hasTAE = false; // No TAE trail
        // properties.hasTFE = false; // No TFE trail
        return properties;
    }

    // Check if all nonzero degree vertices are connected
    vector<bool> visited(n, false);
    bfs(graph,nonZeroDegreeVertex,visited);
   
    properties.startTFE = nonZeroDegreeVertex;
    for (int i = 0; i < n; ++i)
    {
        if (graph.getVertexDegree(i) > 0 && !visited[i])
        {
            properties.isEulerian = false; // Found a nonzero degree vertex that is not connected
            return properties;
        }
    }

    properties.isEulerian = true; // All conditions for Eulerian trail are satisfied
    oddDegreeCount == 0 ? properties.hasTFE = true : properties.hasTAE = true;
    return properties;
}

vector<Edge> fleury_algorithm(const Graph &graph, EulerianTrailProperties &properties)
{
    vector<Edge> trail;      // Keeps edges in order of traversal
    Graph graphCopy = graph; // Cópia para manipulação
    int startVertex = properties.hasTAE ? properties.startTAE : properties.startTFE;
    int currentVertex = startVertex;

    while (graphCopy.getVertexDegree(currentVertex) > 0)
    {
        // Procura uma aresta que não seja ponte
        auto adj = graphCopy.getAdjacencyList(currentVertex);
        int nextVertex = -1;
        while (adj != nullptr)
        {
            int candidate = adj->vertex;
            // Se só existe uma aresta, tem que ser ela
            if (graphCopy.getVertexDegree(currentVertex) == 1 || !isBridge(graphCopy, currentVertex, candidate))
            {
                nextVertex = candidate;
                break;
            }
            adj = adj->next;
        }
        if (nextVertex == -1)
            break; // Nenhuma aresta disponível

        // Adiciona a aresta ao trilha
        trail.push_back(Edge(currentVertex, nextVertex, 1));
        // Remove a aresta do grafo
        graphCopy.removeEdge(currentVertex, nextVertex);
        // Avança para o próximo vértice
        currentVertex = nextVertex;
    }

    return trail;
}