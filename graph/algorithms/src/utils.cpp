#include "utils.hpp"

void bfs(const Graph &graph, int vertice, vector<bool> &visited)
{
    visited[vertice] = true;
    queue<int> queue;
    queue.push(vertice);
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
}

void dfs(const Graph &graph, int vertice, vector<bool> &visited){
    visited[vertice] = true;
    stack<int> s;
    s.push(vertice);
    while(!s.empty())
    {
        int u = s.top();
        s.pop();
        auto current = graph.getAdjacencyList(u);
        while(current!=nullptr)
        {
            int w = current->vertex;
            current = current->next;
            if(!visited[w])
            {
                visited[w] = true;
                s.push(w);
            }
        }
    }
}

bool isBridge(Graph &graph, int u, int v)
{
    // Remove a aresta (u, v) temporariamente
    graph.removeEdge(u, v);
    // Faz uma busca em largura (BFS) ou profundidade (DFS) a partir de u
    // e verifica se v é alcançável
    
    vector<bool> visited(graph.getOrder(), false);
    bfs(graph, u, visited);

    // Recoloca a aresta (u, v)
    graph.addEdge(u, v);
    // Se v não foi visitado, então (u, v) é ponte
    return !visited[v];
};
