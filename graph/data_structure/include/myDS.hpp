#ifndef MYDS_HPP
#define MYDS_HPP

#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <memory>
using namespace std;

namespace MyDataStructures
{

    /**
     * @brief Node structure for the adjacency list
     */
    struct Node
    {
        int vertex;                 // The vertex that makes an edge with the vertex of its list index
        int weight;                 // Weight of the edge (default is 1 for unweighted graphs)
        std::shared_ptr<Node> next; // Pointer to the next node in the list

        Node(int v, int w = 1) : vertex(v), weight(w), next(nullptr) {}
    };

    /**
     * @brief Structure to represent an edge in the graph
     */
    struct Edge
    {
        int u;      // First vertex
        int v;      // Second vertex
        int weight; // Weight of the edge

        Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
    };

    struct EulerianTrailProperties
    {
        bool isEulerian; // True if the graph has an Eulerian trail
        bool hasTFE; // True if the graph has a TFE (Trail Fechada de Euler) trail
        bool hasTAE; // True if the graph has a TAE (Trilha Aberta de Euler) trail
        int startTFE; // Start vertex of the TFE trail
        int startTAE; // Start vertex of the TAE trail
        int endTAE;   // End vertex of the TAE trail

        EulerianTrailProperties() : isEulerian(false), hasTFE(false), hasTAE(false), startTAE(-1), endTAE(-1) {}

        // int startVertex;    // Start of the Eulerian Trail
        // int endVertex; //End of the Eulerian Trail
        // std::shared_ptr<Node> next;  // Pointer to the next node in the list

        // EulerianTrack(int vS, int vE) : startVertex(vS), endVertex(vE), next(nullptr) {}
    };

    // Union-Find (Disjoint Set Union)
    class UnionFind
    {
        vector<int> parent, rank;

    public:
        UnionFind(int n) : parent(n + 1), rank(n + 1, 0)
        {
            for (int i = 1; i <= n; ++i)
                parent[i] = i;
        }
        int find(int x)
        {
            if (parent[x] != x)
                parent[x] = find(parent[x]); // Path compression
            return parent[x];
        }
        void unite(int x, int y)
        {
            int rx = find(x), ry = find(y);
            if (rx == ry)
                return;
            if (rank[rx] < rank[ry])
                parent[rx] = ry;
            else
            {
                parent[ry] = rx;
                if (rank[rx] == rank[ry])
                    rank[rx]++;
            }
        }
    };

} // namespace MyDataStructures

#endif // MYDS_HPP