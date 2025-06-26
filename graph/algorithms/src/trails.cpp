#include "trails.hpp"
#include <functional>

EulerianTrailProperties getEulerianPropetiesOfGraph(const Graph &graph) {
    // An undirected graph is Eulerian if all vertices with nonzero degree have even degree, or if the graph has exactaly 2 vertices with odd degree
    // and all vertices with nonzero degree are connected.
    EulerianTrailProperties properties;
    int oddDegreeCount = 0;
    int n = graph.getOrder();
    int nonZeroDegreeVertex = -1;

    // Find a vertex with nonzero degree to start DFS
    for (int i = 0; i < n; ++i) {
        if (graph.getVertexDegree(i) > 0) {
            nonZeroDegreeVertex = i;
            break;
        }
    }
    if (nonZeroDegreeVertex == -1) {
        // No edges in the graph
        // return false;
        properties.isEulerian = false;
        return properties;
    }

    // Check all vertices have even degree
    for (int i = 0; i < n; ++i) {
        if (graph.getVertexDegree(i) % 2 != 0) {
            oddDegreeCount++;
            oddDegreeCount == 1 ? properties.startTAE = i : properties.endTAE = i;
        }
    }

    if (oddDegreeCount != 2 && oddDegreeCount != 0) {
        properties.isEulerian = false; // More than 2 vertices with odd degree
        // properties.hasTAE = false; // No TAE trail
        // properties.hasTFE = false; // No TFE trail
        return properties;
    }

    // Check if all nonzero degree vertices are connected
    std::vector<bool> visited(n, false);
    std::function<void(int)> dfs = [&](int v) {
        visited[v] = true;
      	queue<int> queue;
        queue.push(v);
        while (!queue.empty())
        {
            int u = queue.front();
            queue.pop();
            auto current = graph.getAdjacencyList(u);
            // Fazendo a travecia na lista ligada
            while (current != nullptr)
            {
                int w = current->vertex;
                current = current->next;
                if (visited[w] == false)
                {
                    visited[w] = true;
                    queue.push(w);
                }
            }
        }
        // for (int u : graph.getAdjacencyList(v)) {
        //     if (!visited[u]) {
        //         dfs(u);
        //     }
        // }
    };
    
    dfs(nonZeroDegreeVertex);
    properties.startTFE = nonZeroDegreeVertex;

    for (int i = 0; i < n; ++i) {
        if (graph.getVertexDegree(i) > 0 && !visited[i]) {
            properties.isEulerian = false; // Found a nonzero degree vertex that is not connected
            return properties;
        }
    }

    properties.isEulerian = true; // All conditions for Eulerian trail are satisfied
    oddDegreeCount == 0 ? properties.hasTFE = true : properties.hasTAE = true;
    return properties;
}