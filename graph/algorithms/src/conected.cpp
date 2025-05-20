#include "graph.hpp"
#include <queue>
#include "connected.hpp"

/**
Complexidade temporal O(n+m)
Complexidade espacial O(n) 

Algoritmo conexo
ENTRADA: Grafo G Com n vértices e m arestas
SAIDA: Verdadeiro se G é conexo, Falso caso contrário

SE n <= 1 DEVOLVA Verdadeiro E PARE
PARA i=2 ATÉ n:
	visitado[i] = Falso
visitado[1] = Verdadeiro
CRIE UMA FILA F COM N POSIÇÕES
INSIRA O VERTICE 1 NA FILA
ENQUANTO F NÃO FOR VAZIA:
	REMOVA DE F OBTENDO u
	PARA CADA VERTICE w ADJASCENTE A u
		SE visitado[w] == Falso
			visitado[w] = verdadeiro
			INSIRA w EM F
SE EXISTIR VERTICE V TAL QUE visitado[V] == Falso
	DEVOLVA Verdadeiro E PARE
SENÃO
	DEVOLVA Falso
 */
using namespace std;

bool is_connected(const Graph &graph)
{
	int n = graph.getOrder();
	vector<bool> visited(n + 1);
	if (n <= 1)
		return true;

	for (int i = 2; i <= n; i++)
	{
		visited[i] = false;
	}
	visited[1] = true;
	queue<int> queue;
	queue.push(1);
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

	for (int j = 1; j <= n; j++)
	{
		if (visited[j] == false)
			return false;
	}
	return true;
}

/**
Complexidade temporal O(n+m)
Complexidade espacial O(n)  

Algoritmo quantidade de vertices na componente conexa
ENTRADA: Grafo G Com n vértices e m arestas e um vertice v
SAIDA: A quantidade de vertices na componente conexa de v

PARA i=1 ATÉ n:
	visitado[i] = Falso
visitado[v] = Verdadeiro
CRIE UMA FILA F COM N POSIÇÕES
INSIRA O VERTICE v NA FILA
FAÇA COUNT=1
ENQUANTO F NÃO FOR VAZIA:
	REMOVA DE F OBTENDO u
	PARA CADA VERTICE w ADJASCENTE A u
		SE visitado[w] == Falso
			visitado[w] = verdadeiro
			INSIRA w EM F
			COUNT++
DEVOLVA COUNT
 */
int vertices_amount_in_connected_component(const Graph &graph, int v)
{
	int n = graph.getOrder();
	vector<bool> visited(n + 1);

	for (int i = 1; i <= n; i++)
	{
		visited[i] = false;
	}
	visited[v] = true;
	queue<int> queue;
	queue.push(v);
	int count = 1;
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
				count++;
			}
		}
	}
	return count;
}

/**
Complexidade temporal O(n+m)
Complexidade espacial O(n)  

Algoritmo quantidade de componentes conexas
ENTRADA: Grafo G Com n vértices e m arestas
SAIDA: A quantidade de componentes conexas em G

FAÇA COUNT=0
PARA i=1 ATÉ n:
	visitado[i] = Falso
CRIE UMA FILA F COM N POSIÇÕES

PARA i=1 ATÈ n:
	SE visitado[i]=Falso
		COUNT++
		INSIRA O VERTICE i NA FILA F
		visitado[i] = Verdadeiro

		ENQUANTO F NÃO FOR VAZIA:
			REMOVA DE F OBTENDO u
			PARA CADA VERTICE w ADJASCENTE A u
				SE visitado[w] == Falso
					visitado[w] = verdadeiro
					INSIRA w EM F
DEVOLVA COUNT
**/
int connected_component_amount(const Graph &graph)
{

	int n = graph.getOrder();
	// vetor de visitados, indexado de 1 a n
	vector<bool> visited(n + 1, false);
	int count = 0;
	queue<int> q;

	// varre todos os vértices; toda vez que encontrar um não visitado,
	// inicia uma BFS para marcar toda a sua componente
	for (int i = 1; i <= n; ++i)
	{
		if (!visited[i])
		{
			++count; // nova componente encontrada
			visited[i] = true;
			q.push(i);

			// BFS para marcar todos os vértices conectados a i
			while (!q.empty())
			{
				int u = q.front();
				q.pop();
				auto current = graph.getAdjacencyList(u);
				while (current != nullptr)
				{
					int w = current->vertex;
					if (!visited[w])
					{
						visited[w] = true;
						q.push(w);
					}
					current = current->next;
				}
			}
		}
	}

	return count;
}

/***
Algoritmo ARESTA-CONEXO
ENTRADA: Um grafo G com n vertices e m arestas, e um inteiro k
SAIDA: SIM se G for k-aresta-conexo, NÃO caso contrário

SE k > deltinha(G) DEVOLVA NÂO E PARE
SE G FOR COMPLETO DEVOLVA SIM E PARE
SE k=1 DEVOLVA CONEXO(G) E PARE

PARA i=1 ATÉ m:
	G' = G - {Aresta i}
	SE ARESTA-CONEXO(G',k-1) = NÃO
		DEVOLVA NÃO E PARE

DEVOLVA SIM E PARE

 */
bool is_k_edge_connected(Graph &graph, int k) {
    // Obtém o número de vértices do grafo
    int n = graph.getOrder();
    // Obtém o número de arestas do grafo
    int m = graph.getSize();

    // Se k for maior que o grau máximo do grafo, não pode ser k-aresta-conexo
    if (k > graph.getMaxDegree()) 
        return false;
    // Se o grafo já for completo (m == n*(n-1)/2), então é k-aresta-conexo para qualquer k ≤ n-1
    if (m == n * (n - 1) / 2)          
        return true;
    // Caso base: 1-aresta-conexo é equivalente a simplesmente conexo
    if (k == 1)                  
        return is_connected(graph);

    // Coleta todas as arestas (u,v) com u < v para evitar duplicatas
    std::vector<std::pair<int,int>> edges;
    for (int u = 1; u <= n; ++u) {
        // Ponteiro para percorrer a lista de adjacência do vértice u
        auto adj = graph.getAdjacencyList(u);
        while (adj) {
            // Se for aresta u→v com u < v, armazena o par
            if (u < adj->vertex)
                edges.emplace_back(u, adj->vertex);
            // Avança para o próximo nó da lista
            adj = adj->next;
        }
    }

    // Para cada aresta coletada, remove-a, testa recursivamente e depois restaura
    for (auto &e : edges) {
        int u = e.first;   // primeiro vértice da aresta
        int v = e.second;  // segundo vértice da aresta
        // Remove a aresta (u,v) do grafo
        graph.removeEdge(u, v);
        // Verifica se o grafo modificado é (k-1)-aresta-conexo
        bool ok = is_k_edge_connected(graph, k - 1);
        // Restaura a aresta removida para manter o grafo original intacto
        graph.addEdge(u, v);
        // Se em alguma remoção o grafo não for (k-1)-aresta-conexo, devolve falso
        if (!ok) 
            return false;
    }
    // Se todas as remoções passaram no teste, o grafo é k-aresta-conexo
    return true;
}


// bool is_k_edge_connected(const Graph &graph, int k)
// {
// 	if(k > graph.getMaxDegree())
// 		return false;
// 	if(graph.getSize() == graph.getOrder() * (graph.getOrder() - 1) / 2)
// 		return true;
// 	if(k == 1)
// 		return is_connected(graph);
	
// 	// Iterate through all vertices
// 	for(int i = 1; i <= graph.getOrder(); i++) {
// 		auto current = graph.getAdjacencyList(i);
// 		// Iterate through all edges of vertex i
// 		while(current != nullptr) {
// 			int j = current->vertex;
// 			// Only process each edge once (i < j)
// 			if(i < j) {
// 				Graph g_prime = graph;
// 				g_prime.removeEdge(i, j);
// 				if(!is_k_edge_connected(g_prime, k - 1))
// 					return false;
// 			}
// 			current = current->next;
// 		}
// 	}
// 	return true;
// }

