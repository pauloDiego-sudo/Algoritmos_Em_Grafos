#include "minimum_spanning_tree.hpp"
#include "connected.hpp"
#include <algorithm>
#include <vector>

// print the mst
void print_mst(const vector<Edge> &mst)
{
    for (const Edge &edge : mst)
    {
        cout << edge.u << " " << edge.v << " " << edge.weight << endl;
    }
}

vector<Edge> kruskal_mst_naive(const Graph &graph)
{
    int n = graph.getOrder();
    vector<Edge> T; // MST edges
    vector<Edge> edges;

    // Collect all edges from the graph
    for (int u = 1; u <= n; ++u)
    {
        auto current = graph.getAdjacencyList(u);
        while (current != nullptr)
        {
            if (u < current->vertex)
            {
                edges.emplace_back(u, current->vertex, current->weight);
            }
            current = current->next;
        }
    }

    // Sort edges by weight (COLOQUE AS ARESTAS DE G EM ORDEM CRESCENTE DE CUSTO)
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
         { return a.weight < b.weight; });

    // Create a temporary graph to check for cycles
    Graph temp_graph(n, true); // true for weighted graph

    // Process edges until we have n-1 edges in the MST
    for (const Edge &edge : edges)
    {
        // ENQUANTO |T| < n-1
        if (T.size() >= n - 1)
            break;

        // Add the edge to the temporary graph
        temp_graph.addEdge(edge.u, edge.v, edge.weight);

        // SE G[T U {aresta_i}] FOR ACICLICO
        if (is_forest(temp_graph))
        {
            // T = T U {aresta_i}
            T.push_back(edge);
        }
        else
        {
            // Remove the edge if it creates a cycle
            temp_graph.removeEdge(edge.u, edge.v);
        }
    }

    return T;
}

/**
Abaixo temos o algoritmo de kruskal otimizado em relação a checagem de ciclos.
Esse algoritmo foi implementado duas vezes, uma com pintura de cores e outra com Union-Find.
Representando a mesma ideia, a otimização reduz a complexidade temporal de O(n*m) para O(m*log(n))
*/

vector<Edge> kruskal_mst_paint(const Graph &graph)
{
    int n = graph.getOrder();
    vector<Edge> T;
    vector<Edge> edges;
    vector<int> color(n + 1, 0); // 0 = incolor
    int next_color = 1;

    // Coleta todas as arestas
    for (int u = 1; u <= n; ++u)
    {
        auto current = graph.getAdjacencyList(u);
        while (current != nullptr)
        {
            if (u < current->vertex)
            {
                edges.emplace_back(u, current->vertex, current->weight);
            }
            current = current->next;
        }
    }

    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
         { return a.weight < b.weight; });

    for (const Edge &edge : edges)
    {
        int color_u = color[edge.u];
        int color_v = color[edge.v];
        if (T.size() >= n - 1)
            break;

        if (color_u == 0 && color_v == 0)
        {
            // Ambos incolores: nova cor
            color[edge.u] = color[edge.v] = next_color++;
            T.push_back(edge);
        }
        else if (color_u == 0)
        {
            // u incolor, v colorido
            color[edge.u] = color_v;
            T.push_back(edge);
        }
        else if (color_v == 0)
        {
            // v incolor, u colorido
            color[edge.v] = color_u;
            T.push_back(edge);
        }
        else if (color_u != color_v)
        {
            // Cores diferentes: unir componentes
            // Pinta todos da menor componente com a cor da maior
            int count_color_u = count(color.begin(), color.end(), color_u);
            int count_color_v = count(color.begin(), color.end(), color_v);
            int from = (count_color_u < count_color_v) ? color_u : color_v;
            int to = (count_color_u < count_color_v) ? color_v : color_u;
            for (int i = 1; i <= n; ++i)
            {
                if (color[i] == from)
                    color[i] = to;
            }
            T.push_back(edge);
        }
        // else: mesma cor, formaria ciclo, ignora
    }
    return T;
}

vector<Edge> kruskal_mst(const Graph &graph)
{
    int n = graph.getOrder();
    vector<Edge> T; // MST edges
    vector<Edge> edges;

    // Coleta todas as arestas do grafo
    for (int u = 1; u <= n; ++u)
    {
        auto current = graph.getAdjacencyList(u);
        while (current != nullptr)
        {
            if (u < current->vertex)
            {
                edges.emplace_back(u, current->vertex, current->weight);
            }
            current = current->next;
        }
    }

    // Ordena as arestas por peso
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
         { return a.weight < b.weight; });

    UnionFind uf(n);

    // Processa as arestas em ordem crescente de peso
    for (const Edge &edge : edges)
    {
        if (T.size() >= n - 1)
            break;
        int u_set = uf.find(edge.u);
        int v_set = uf.find(edge.v);
        if (u_set != v_set)
        {
            T.push_back(edge);
            uf.unite(u_set, v_set);
        }
    }
    return T;
}

vector<Edge> prim_mst_naive(const Graph &graph)
{
    int n = graph.getOrder();
    vector<Edge> T; // T = {}
    vector<bool> in_tree(n + 1, false);
    in_tree[1] = true; // Z = {Vertice 1}

    for (int count = 1; count < n; ++count) // ENQUANTO EXISTIR VERTICE V NA FRONTEIRA DE Z
    {
        int min_weight = INT_MAX;
        int u_min = -1, v_min = -1;

        // Procura a menor aresta na fronteira
        for (int u = 1; u <= n; ++u)
        {
            if (!in_tree[u]) continue; // u ∈ Z
            auto current = graph.getAdjacencyList(u);
            while (current != nullptr)
            {
                int v = current->vertex;
                int w = current->weight;
                if (!in_tree[v] && w < min_weight) // v ∉ Z e custo mínimo
                {
                    min_weight = w;
                    u_min = u;
                    v_min = v;
                }
                current = current->next;
            }
        }

        if (u_min != -1 && v_min != -1)
        {
            T.emplace_back(u_min, v_min, min_weight); // T = T U {Aresta uv}
            in_tree[v_min] = true;                    // Z = Z U {Vertice v}
        }
    }
    return T; // DEVOLVA T
}
