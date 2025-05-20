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
Complexidade temporal O(m^k)
Complexidade espacial O(m)

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

bool is_k_edge_connected(Graph &graph, int k)
{
	int n = graph.getOrder();
	int m = graph.getSize();

	if (k > graph.getMaxDegree())
		return false;

	if (m == n * (n - 1) / 2)
		return true;

	if (k == 1)
		return is_connected(graph);

	for (int i = 1; i <= m; ++i)
	{
		Graph g = graph;
		// We need to find the actual edge vertices first
		std::vector<std::pair<int, int>> edges;
		for (int u = 1; u <= n; ++u)
		{
			auto adj = graph.getAdjacencyList(u);
			while (adj)
			{
				if (u < adj->vertex)
					edges.emplace_back(u, adj->vertex);
				adj = adj->next;
			}
		}
		// Now use the actual vertices to remove the edge
		g.removeEdge(edges[i - 1].first, edges[i - 1].second);
		if (!is_k_edge_connected(g, k - 1))
			return false;
	}
	return true;
}

/***
Complexidade temporal O(n^(k+1))
Complexidade espacial O(n)

Algoritmo VERTICE-CONEXO
ENTRADA: Um grafo G com n vertices e m arestas, e um inteiro k
SAIDA: SIM se G for k-vertice-conexo, NÃO caso contrário

SE G FOR COMPLETO DEVOLVA SIM E PARE
SE k > deltinha(G) DEVOLVA NÂO E PARE
SE k=1 DEVOLVA CONEXO(G) E PARE

PARA i=1 ATÉ n:
	G' = G - {Vertice i}
	SE VERTICE-CONEXO(G',k-1) = NÃO
		DEVOLVA NÃO E PARE

DEVOLVA SIM E PARE

 */

bool is_k_vertex_connected(Graph &graph, int k)
{
	int n = graph.getOrder();
	int m = graph.getSize();

	if (m == n * (n - 1) / 2)
		return true;

	if (k > graph.getMinDegree())
		return false;

	if (k == 1)
		return is_connected(graph);

	for (int v = 1; v <= n; ++v)
	{
		Graph g = graph;
		g.removeVertex(v);
		if (!is_k_vertex_connected(g, k - 1))
		{
			return false;
		}
	}
	return true;
}

/**
 Algoritmo Floresta
 ENTRADA: Um grafo G com n vertices e m arestas
 SAIDA: SIM, se G for uma floresta, NÂO, caso contrário

 SE n=0 DEVOLVA SIM E PARE
 SE m >= n DEVOLVA NÃO E PARE

 PARA i=1 ATÉ n:
	visitado[i]=FALSO
	anterior[i]=0

CRIE UMA FILA F COM n POSIÇÕES
ENQUANTO EXISTIR VERTICE V TAL QUE visitado[v]=falso
	visitado[v]=verdadeiro
	INSIRA v EM F
	ENQUANTO F NÃO FOR VAZIA
		REMOVA DE F OBTENDO u
		PARA CADA VERTICE w ADJASCENTE A u
			SE anterior[u] != w
				SE visitado[w] = verdaeiro
					DEVOLVA NÂO E PARE
				SENÃo
					visitado[w]=verdadeiro
					anterior[w]=u
					INSIRA w EM F
DEVOLVA SIM

 */

bool is_forest(Graph &graph)
{
	// Obtém o número de vértices e arestas
	int n = graph.getOrder();
	int m = graph.getSize();

	// Se o grafo está vazio, é uma floresta
	if (n == 0)
		return true;

	// Se tem mais arestas que vértices, não é uma floresta
	if (m >= n)
		return false;

	// Inicializa vetores de visitados e anteriores
	vector<bool> visited(n + 1, false);
	vector<int> previous(n + 1, 0);
	queue<int> q;

	// Para cada vértice não visitado, inicia uma BFS
	for (int i = 1; i <= n; ++i)
	{
		if (!visited[i])
		{
			// Marca o vértice como visitado
			visited[i] = true;
			q.push(i);

			// BFS para detectar ciclos
			while (!q.empty())
			{
				int u = q.front();
				q.pop();

				// Percorre todos os vértices adjacentes
				auto current = graph.getAdjacencyList(u);
				while (current != nullptr)
				{
					int w = current->vertex;
					// Se não é o vértice anterior
					if (previous[u] != w)
					{
						// Se já foi visitado, existe um ciclo
						if (visited[w])
						{
							return false;
						}
						else
						{
							visited[w] = true;
							previous[w] = u;
							q.push(w);
						}
					}
					current = current->next;
				}
			}
		}
	}
	// Se não encontrou ciclos, é uma floresta
	return true;
}