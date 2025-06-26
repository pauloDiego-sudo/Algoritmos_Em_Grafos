/**
 * @brief   Algoritmo de Dijkstra usando Min Heap
 * @details O programa recebe o nome de um arquivo contendo a descrição de um grafo direcionado via linha de comando.
 *          O arquivo fornecido ao programa deve ter o seguinte formato:
 *          n m s t
 *          u1 v1 c1
 *          u2 v2 c2
 *          ...
 *          um vm cm
 *          onde n é o número de vértices, m é o número de arcos,
 *          s é o vértice de origem, t é o vértice de destino,
 *          ui e vi são a origem e o destino do arco i e ci é o custo do arco i.
 *          Utilizando o algoritmo de Dijkstra, o programa calcula e exibe um caminho de custo mínimo de s até t.
 * @author  Paulo Diego De Meneses
 * @author  Vinicius Menezes Monte
 * @author  Douglas Cartaxo
 * @author  Vladmir Rodaly Joseph
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define INF INT32_MAX

/* ============================================================================= */
/* ============================================================================= */
/* ======================= DEFINIÇÕES E ESTRUTURAS ============================== */
/* ============================================================================= */
/* ============================================================================= */

/**
 * @brief Nó da lista de adjacência que representa o grafo
 */
typedef struct node
{
    int32_t vertex;    /* vértice que faz um arco com o vértice deste nó da lista */
    int32_t cost;      /* custo do arco */
    struct node *next; /* ponteiro para o próximo nó da lista */
} node_t;

/**
 * @brief Estrutura que representa um arco ou item da heap
 */
typedef struct arc
{
    int32_t vertex_u; /* vértice de origem do arco */
    int32_t vertex_v; /* vértice de destino do arco */
    int32_t cost;     /* custo ou prioridade */
} arc_t;

/**
 * @brief Estrutura de heap de arcos
 */
typedef struct heap
{
    int32_t size;     /* número de elementos na heap */
    int32_t capacity; /* capacidade máxima da heap */
    arc_t *elements;  /* vetor de arcos */
} heap_t;

/* ============================================================================= */
/* ============================================================================= */
/* ======================= PROTÓTIPOS DAS FUNÇÕES ============================== */
/* ============================================================================= */
/* ============================================================================= */

/* ============================================================================= */
/* ======================= GRAFO E LISTA DE ADJACÊNCIA ========================== */
/* ============================================================================= */

/**
 * @brief Cria o grafo a partir de um arquivo
 * @param filename Nome do arquivo de entrada
 * @param graph Ponteiro para o grafo (lista de adjacência)
 * @param vertices Ponteiro para o número de vértices
 * @param edges Ponteiro para o número de arcos
 * @param source Ponteiro para o vértice de origem
 * @param target Ponteiro para o vértice de destino
 * @return 0 em caso de sucesso, 1 em caso de erro
 */
uint8_t create_graph(const char *filename, node_t **graph,
                     int32_t *vertices, int32_t *edges,
                     int32_t *source, int32_t *target);

/**
 * @brief Insere um novo nó na lista de adjacência
 * @param list Lista de adjacência
 * @param vertex Vértice a ser inserido
 * @param cost Custo do arco
 * @return 0 em caso de sucesso, 1 em caso de erro
 */
uint8_t insert_to_list(node_t *list, int32_t vertex, int32_t cost);

/* ============================================================================= */
/* ======================= HEAP DE MINIMOS ======================================= */
/* ============================================================================= */

/**
 * @brief Cria uma heap com capacidade especificada
 * @param capacity Capacidade máxima do heap
 * @return Ponteiro para a heap criada
 */
heap_t *create_heap(int32_t capacity);

/**
 * @brief Insere um arco na heap
 * @param heap Ponteiro para a heap
 * @param arc Arco a ser inserido
 */
void insert_to_heap(heap_t *heap, arc_t arc);

/**
 * @brief Rearranja a heap após a inserção de um novo arco, garantindo a propriedade de heap mínima.
 * @param heap Ponteiro para a heap
 * @param index Índice do elemento recém-inserido que pode violar a propriedade da heap
 */
void rearrange_heap(heap_t *heap, int32_t index);

/**
 * @brief Garante a propriedade de heap mínima a partir de um índice, reorganizando os elementos se necessário.
 * @param heap Ponteiro para a heap
 * @param index Índice inicial para reorganização
 */
void heapify(heap_t *heap, int32_t index);

/**
 * @brief Remove e retorna o arco de menor custo da heap
 * @param heap Ponteiro para a heap
 * @return Arco de menor custo
 */
arc_t remove_from_heap(heap_t *heap);

/* ============================================================================= */
/* ======================= ALGORITMO DE DIJKSTRA =============================== */
/* ============================================================================= */

/**
 * @brief Executa o algoritmo de Dijkstra para encontrar o caminho mínimo
 * @param graph Ponteiro para o grafo (lista de adjacência)
 * @param n Número de vértices
 * @param m Número de arcos
 * @param source Vértice de origem
 * @param target Vértice de destino
 * @return 0 em caso de sucesso, 1 em caso de erro
 */
uint8_t dijkstra(node_t **graph, int32_t n, int32_t m,
                 int32_t source, int32_t target);

/* ============================================================================= */
/* ======================= FUNÇÕES AUXILIARES ================================== */
/* ============================================================================= */
/**
 * @brief Exibe a lista de adjacências do grafo
 * @param graph Ponteiro para o grafo (lista de adjacência)
 * @param n Número de vértices
 */
void show_graph_list(node_t *graph, int32_t n);

/* ============================================================================= */
/* ============================================================================= */
/* ======================= IMPLEMENTAÇÃO DAS FUNÇÕES =========================== */
/* ============================================================================= */
/* ============================================================================= */

/**
 * @brief Função principal do programa
 * @param argc Número de argumentos da linha de comando
 * @param argv Vetor de argumentos da linha de comando
 * @return 0 em caso de sucesso, 1 em caso de erro
 */
int main(int argc, char const *argv[])
{
    //Verifica se o arquivo foi fornecido
    if (argc < 2)
    {
        printf("Insira o nome do arquivo ao executar o programa.\n");
        printf("Ex: $ ./ep1 grafo.txt\n");
        return 1;
    }

    //Cria o grafo a partir do arquivo
    int32_t vertices, arcs, s, t;
    node_t *graph = NULL;
    if (create_graph(argv[1], &graph, &vertices, &arcs, &s, &t))
    {
        return 1;
    }

    //Executa o algoritmo de Dijkstra
    if (dijkstra(&graph, vertices, arcs, s, t))
    {
        return 1;
    }

    //Exibe a lista de adjacências do grafo
    // show_graph_list(graph, vertices);

    return 0;
}

/* ============================================================================= */
/* ======================= GRAFO E LISTA DE ADJACÊNCIA ========================== */
/* ============================================================================= */

uint8_t create_graph(const char *filename, node_t **graph,
                     int32_t *vertices, int32_t *arcs,
                     int32_t *source, int32_t *target)
{
    //Abre o arquivo
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    //Lê a primeira linha do arquivo
    char line[64];
    if (fgets(line, sizeof(line), file) == NULL)
    {
        printf("Erro ao ler arquivo\n");
        return 1;
    }

    //Lê os vértices, arcos, origem e destino e verifica se o layout do arquivo está correto
    if (sscanf(line, "%d %d %d %d", vertices, arcs, source, target) != 4)
    {
        printf("Erro no layout do arquivo (deve ser: n m s t)\n");
        return 1;
    }

    //Aloca memória para o grafo
    *graph = calloc((*vertices + 1), sizeof(node_t));
    if (*graph == NULL)
    {
        printf("Erro ao alocar espaço para o grafo\n");
        return 1;
    }

    //Lê os arcos e insere na lista de adjacência
    for (int32_t i = 0; i < *arcs; i++)
    {
        //Lê a linha do arquivo
        if (fgets(line, sizeof(line), file) == NULL)
        {
            printf("Erro ao ler arquivo\n");
            return 1;
        }
        //Lê os vértices e o custo do arco
        int32_t u, v, c;
        if (sscanf(line, "%d %d %d", &u, &v, &c) != 3)
        {
            printf("Erro no layout do arquivo\n");
            return 1;
        }
        //Insere o arco na lista de adjacência
        if (insert_to_list(&(*graph)[u], v, c))
        {
            return 1;
        }
    }

    //Fecha o arquivo
    fclose(file);
    return 0;
}


uint8_t insert_to_list(node_t *list, int32_t vertex, int32_t cost)
{
    //Aloca memória para o novo nó
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL)
    {
        printf("Erro ao alocar espaço para o grafo\n");
        return 1;
    }
    //Insere o vértice e o custo do arco no novo nó
    new->vertex = vertex;
    new->cost = cost;
    //Insere o novo nó na lista de adjacência
    new->next = list->next;
    list->next = new;
    return 0;
}

/* ============================================================================= */
/* ======================= HEAP DE MINIMOS ======================================= */
/* ============================================================================= */

heap_t *create_heap(int32_t capacity)
{
    //Aloca memória para a heap
    heap_t *h = malloc(sizeof(heap_t));
    if (h == NULL)
    {
        printf("Erro ao alocar espaço para a heap\n");
        return NULL;
    }
    //Inicializa a heap
    h->size = 0;
    h->capacity = capacity;
    //Aloca memória para os elementos do heap
    h->elements = malloc(capacity * sizeof(arc_t));
    if (h->elements == NULL)
    {
        printf("Erro ao alocar espaço para os arcos\n");
        free(h);
        return NULL;
    }
    //Retorna o ponteiro para o heap
    return h;
}

void insert_to_heap(heap_t *heap, arc_t arc)
{
    //Se o heap estiver cheio, não insere o arco
    if (heap->size >= heap->capacity)
    {
        printf("Erro: heap cheia\n");
        return;
    }
    //Insere o arco no heap
    heap->elements[heap->size] = arc;
    //Rearranja o heap para manter a propriedade de heap mínima
    rearrange_heap(heap, heap->size);
    heap->size++;
}

void rearrange_heap(heap_t *heap, int32_t i)
{
    //Se o arco for a raiz, não é necessário rearranjar o heap
    if (i <= 0)
    {
        return;
    }
    //Encontra o pai do arco
    int32_t parent = (i - 1) / 2;
    arc_t *parent_arc = &heap->elements[parent];
    arc_t *current_arc = &heap->elements[i];
    //Se o custo do arco for menor que o custo do pai, troca os arcos
    if (current_arc->cost < parent_arc->cost)
    {
        arc_t tmp = *parent_arc;
        *parent_arc = *current_arc;
        *current_arc = tmp;
        // chama a função recursivamente com o novo índice do arco
        rearrange_heap(heap, parent);
    }
}

arc_t remove_from_heap(heap_t *heap)
{
    //Remove o arco da raiz
    arc_t root = heap->elements[0];
    //Substitui o arco da raiz pelo último arco da heap
    heap->elements[0] = heap->elements[--heap->size];
    //Rearranja a heap (sift down)
    heapify(heap, 0);
    //Retorna o arco removido
    return root;
}

void heapify(heap_t *heap, int32_t i)
{
    //Encontra o filho esquerdo e direito do arco
    int32_t left = 2*i + 1;
    int32_t right = 2*i + 2;
    int32_t smallest = i;
    //Encontra o arco de menor custo entre o arco atual e os filhos
    if (left < heap->size && heap->elements[left].cost < heap->elements[smallest].cost)
        smallest = left;
    if (right < heap->size && heap->elements[right].cost < heap->elements[smallest].cost)
        smallest = right;
    //Se o arco de menor custo não for o arco atual
    if (smallest != i)
    {
        //Troca os arcos
        arc_t tmp = heap->elements[i];
        heap->elements[i] = heap->elements[smallest];
        heap->elements[smallest] = tmp;
        //Chama a função recursivamente com o novo índice do arco
        heapify(heap, smallest);
    }
}

/* ============================================================================= */
/* ======================= FUNÇÕES AUXILIARES ================================== */
/* ============================================================================= */

void show_graph_list(node_t *graph, int32_t n)
{
    printf("Lista de adjacencias:\n");
    for (int32_t i = 1; i <= n; i++)
    {
        printf("%d:", i);
        node_t *atual = graph[i].next;
        //Exibe os arcos incidentes ao vértice i
        while (atual != NULL)
        {
            printf(" -> (%d, custo=%d)", atual->vertex, atual->cost);
            atual = atual->next;
        }
        printf("\n");
    }
}

/* ============================================================================= */
/* ======================= ALGORITMO DE DIJKSTRA =============================== */
/* ============================================================================= */

uint8_t dijkstra(node_t **graph, int32_t n, int32_t m,
                 int32_t source, int32_t target)
{
    //Aloca memória para os vetores de distância e predecessores
    int32_t *dist = malloc((n + 1) * sizeof(int32_t));
    int32_t *prev = malloc((n + 1) * sizeof(int32_t));
    //Inicializa os vetores com INF e -1
    for (int32_t i = 1; i <= n; i++)
    {
        dist[i] = INF;
        prev[i] = -1;
    }
    //Inicializa a distância do vértice de origem com 0
    dist[source] = 0;

    //Cria o heap com capacidade máxima de m arcos
    heap_t *heap = create_heap(m);
    //Insere o arco (source, source) no heap
    //O custo do arco é 0 porque a distância do vértice de origem para ele mesmo é 0
    insert_to_heap(heap, (arc_t){.vertex_u = source, .vertex_v = source, .cost = 0});

    //Enquanto existir arcos na fronteira de Z
    while (heap->size > 0)
    {
        //Seja a o arco de menor custo na fronteira de Z
        arc_t a = remove_from_heap(heap);
        //u é o vértice de destino do arco a
        int32_t u = a.vertex_v;
        //d é o custo do caminho até o vértice u
        int32_t d = a.cost;
        //Se o custo do arco for maior que o custo do vértice, não é necessário processar
        if (d > dist[u])
            continue;
        //Se o vértice é o destino, o caminho mínimo foi encontrado, portanto, o algoritmo termina
        if (u == target)
            break;
        //Para cada arco (u, v) incidente em u
        for (node_t *nei = (*graph)[u].next; nei != NULL; nei = nei->next)
        {
            //v é o vértice de destino do arco
            int32_t v = nei->vertex;
            //w é o custo do arco
            int32_t w = nei->cost;
            // Se o caminho através de u for mais curto que o caminho atual para v
            if (d + w < dist[v])
            {
                //Atualiza a distância e o antecessor
                dist[v] = d + w;
                prev[v] = u;
                //Insere o arco (u, v) no heap
                insert_to_heap(heap, (arc_t){.vertex_u = u, .vertex_v = v, .cost = dist[v]});
            }
        }
    }

    //Se a distância do vértice de origem para o vértice de destino for INF, não existe caminho
    if (dist[target] == INF)
    {
        printf("Não existe caminho de %d até %d\n", source, target);
        free(dist);
        free(prev);
        free(heap->elements);
        free(heap);
        return 1;
    }

    // Reconstrói o caminho percorrendo os antecessores do vértice de destino até o vértice de origem
    int32_t stack[n];
    int path_len = 0;
    for (int32_t v = target; v != source; v = prev[v])
        stack[path_len++] = v;
    stack[path_len++] = source;

    // Exibe o caminho mínimo e o custo
    printf("Caminho minimo do vertice %d para o vertice %d:", source, target);
    for (int i = path_len - 1; i > 0; i--)
        printf(" (%d, %d)", stack[i], stack[i - 1]);
    printf("\nCusto: %d\n", dist[target]);

    // Libera a memória alocada para os vetores de distância, antecessores e heap
    free(dist);
    free(prev);
    free(heap->elements);
    free(heap);
    return 0;
}
