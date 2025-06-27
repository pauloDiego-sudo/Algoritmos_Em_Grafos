# Pseudo Codes
Este arquivo contém pseudocódigos em português para diversos algoritmos de grafos. Os códigos são escritos em um formato genérico, facilitando a tradução para qualquer linguagem de programação.

## Algoritmo: Verificar se um grafo é conexo

**Complexidade temporal:** O(n + m)  
**Complexidade espacial:** O(n)

**Descrição:**  
Verifica se um grafo $G$ com $n$ vértices e $m$ arestas é conexo.

**Entrada:** Grafo $G$ com $n$ vértices e $m$ arestas  
**Saída:** Verdadeiro se $G$ é conexo, Falso caso contrário

```plaintext
SE n <= 1 DEVOLVA Verdadeiro E PARE
PARA i = 2 ATÉ n:
    visitado[i] = Falso
visitado[1] = Verdadeiro
CRIE UMA FILA F COM N POSIÇÕES
INSIRA O VÉRTICE 1 NA FILA
ENQUANTO F NÃO FOR VAZIA:
    REMOVA DE F OBTENDO u
    PARA CADA VÉRTICE w ADJACENTE A u
        SE visitado[w] == Falso
            visitado[w] = Verdadeiro
            INSIRA w EM F
SE EXISTIR VÉRTICE V TAL QUE visitado[V] == Falso
    DEVOLVA Falso
SENÃO
    DEVOLVA Verdadeiro
```

## Algoritmo: Quantidade de vértices na componente conexa

**Complexidade temporal:** O(n + m)  
**Complexidade espacial:** O(n)

**Descrição:**  
Calcula a quantidade de vértices na componente conexa de um vértice $v$ em um grafo $G$ com $n$ vértices e $m$ arestas.

**Entrada:** Grafo $G$ com $n$ vértices e $m$ arestas, e um vértice $v$  
**Saída:** A quantidade de vértices na componente conexa de $v$

```plaintext
PARA i = 1 ATÉ n:
    visitado[i] = Falso
visitado[v] = Verdadeiro
CRIE UMA FILA F COM N POSIÇÕES
INSIRA O VÉRTICE v NA FILA
COUNT = 1
ENQUANTO F NÃO FOR VAZIA:
    REMOVA DE F OBTENDO u
    PARA CADA VÉRTICE w ADJACENTE A u
        SE visitado[w] == Falso
            visitado[w] = Verdadeiro
            INSIRA w EM F
            COUNT++
DEVOLVA COUNT
```

## Algoritmo: Quantidade de componentes conexas

**Complexidade temporal:** O(n + m)  
**Complexidade espacial:** O(n)

**Descrição:**  
Calcula a quantidade de componentes conexas $w(G)$ em um grafo $G$ com $n$ vértices e $m$ arestas.

**Entrada:** Grafo $G$ com $n$ vértices e $m$ arestas  
**Saída:** A quantidade de componentes conexas em $G$

```plaintext
COUNT = 0
PARA i = 1 ATÉ n:
    visitado[i] = Falso
CRIE UMA FILA F COM N POSIÇÕES

PARA i = 1 ATÉ n:
    SE visitado[i] == Falso
        COUNT++
        INSIRA O VÉRTICE i NA FILA F
        visitado[i] = Verdadeiro

        ENQUANTO F NÃO FOR VAZIA:
            REMOVA DE F OBTENDO u
            PARA CADA VÉRTICE w ADJACENTE A u
                SE visitado[w] == Falso
                    visitado[w] = Verdadeiro
                    INSIRA w EM F
DEVOLVA COUNT
```
## Algoritmo: Verificar se um grafo é k-aresta-conexo

**Complexidade temporal:** O(m^k)  
**Complexidade espacial:** O(m)

**Descrição:**  
Verifica se um grafo $G$ com $n$ vértices e $m$ arestas é $k$-aresta-conexo, ou seja, se é necessário remover pelo menos $k$ arestas para desconectar o grafo.

**Entrada:** Grafo $G$ com $n$ vértices e $m$ arestas, e um inteiro $k$  
**Saída:** SIM se $G$ for $k$-aresta-conexo, NÃO caso contrário

```plaintext
SE k > deltinha(G) DEVOLVA NÂO E PARE
SE G FOR COMPLETO DEVOLVA SIM E PARE
SE k=1 DEVOLVA CONEXO(G) E PARE

PARA i=1 ATÉ m:
	G' = G - {Aresta i}
	SE ARESTA-CONEXO(G',k-1) = NÃO
		DEVOLVA NÃO E PARE

DEVOLVA SIM E PARE
```

## Algoritmo: Verificar se um grafo é k-vértice-conexo

**Complexidade temporal:** O(n<sup>k+1</sup>)  
**Complexidade espacial:** O(n)

**Descrição:**  
Verifica se um grafo $G$ com $n$ vértices e $m$ arestas é $k$-vértice-conexo, ou seja, se é necessário remover pelo menos $k$ vértices para desconectar o grafo.

**Entrada:** Grafo $G$ com $n$ vértices e $m$ arestas, e um inteiro $k$  
**Saída:** SIM se $G$ for $k$-vértice-conexo, NÃO caso contrário

```plaintext
SE G FOR COMPLETO DEVOLVA SIM E PARE
SE k > deltinha(G) DEVOLVA NÃO E PARE
SE k = 1 DEVOLVA CONEXO(G) E PARE

PARA i = 1 ATÉ n:
    G' = G - {Vértice i}
    SE VERTICE-CONEXO(G', k-1) = NÃO
        DEVOLVA NÃO E PARE

DEVOLVA SIM E PARE
```


## Algoritmo: Verificar se um grafo é uma floresta

**Complexidade temporal:** O(n + m)  
**Complexidade espacial:** O(n)

**Descrição:**  
Verifica se um grafo $G$ com $n$ vértices e $m$ arestas é uma floresta (ou seja, um grafo acíclico e sem laços).

**Entrada:** Grafo $G$ com $n$ vértices e $m$ arestas  
**Saída:** SIM, se $G$ for uma floresta; NÃO, caso contrário

```plaintext
SE n = 0 DEVOLVA SIM E PARE
SE m >= n DEVOLVA NÃO E PARE

PARA i = 1 ATÉ n:
    visitado[i] = FALSO
    anterior[i] = 0

CRIE UMA FILA F COM n POSIÇÕES

ENQUANTO EXISTIR VÉRTICE v TAL QUE visitado[v] = FALSO
    visitado[v] = VERDADEIRO
    INSIRA v EM F

    ENQUANTO F NÃO FOR VAZIA:
        REMOVA DE F OBTENDO u
        PARA CADA VÉRTICE w ADJACENTE A u:
            SE anterior[u] != w
                SE visitado[w] = VERDADEIRO
                    DEVOLVA NÃO E PARE
                SENÃO
                    visitado[w] = VERDADEIRO
                    anterior[w] = u
                    INSIRA w EM F

DEVOLVA SIM
```
## Algoritmo: Kruskal (Árvore Geradora Mínima)

**Complexidade temporal:** O(n·m) (ou O(m log n) com union-find)
**Complexidade espacial:** O(n + m)

**Descrição:**  
Encontra uma árvore geradora mínima em um grafo conexo $G$ com $n$ vértices e $m$ arestas, onde cada aresta possui um custo.

**Entrada:** Grafo conexo $G$ com $n$ vértices e $m$ arestas, cada aresta com um custo  
**Saída:** Conjunto de arestas $T$ tal que $G[T]$ é uma árvore geradora mínima de $G$

```plaintext
T = {}
i = 1
COLOQUE AS ARESTAS DE G EM ORDEM CRESCENTE DE CUSTO
ENQUANTO |T| < n-1:
    SE G[T ∪ {aresta_i}] FOR ACÍCLICO
        T = T ∪ {aresta_i}
    i++
DEVOLVA T
```

## Algoritmo: Prim (Árvore Geradora Mínima)

**Complexidade temporal:** O(n·m) (ou O(m log n) com heap)  
**Complexidade espacial:** O(n + m)

**Descrição:**  
Encontra uma árvore geradora mínima em um grafo conexo $G$ com $n$ vértices e $m$ arestas, onde cada aresta possui um custo.

**Entrada:** Grafo conexo $G$ com $n$ vértices e $m$ arestas, cada aresta com um custo  
**Saída:** Conjunto de arestas $T$ tal que $G[T]$ é uma árvore geradora mínima de $G$

```plaintext
T = {}
Z = {Vértice 1}
ENQUANTO EXISTIR VÉRTICE v NA FRONTEIRA DE Z:
    SEJA uv UMA ARESTA NA FRONTEIRA DE Z ONDE u ∈ Z E v ∉ Z, CUJO CUSTO É MÍNIMO
    T = T ∪ {Aresta uv}
    Z = Z ∪ {Vértice v}
DEVOLVA T
```
## Algoritmo: Dijkstra (Caminho Mínimo em Grafos Dirigidos)
**Complexidade temporal:** O(n·m) (ou O(m log n) com heap)  
**Complexidade espacial:** O(n + m)

**Descrição:**  
Encontra o caminho mínimo de um vértice $s$ a um vértice $t$ em um grafo dirigido $G$ com $n$ vértices e $m$ arestas, onde cada aresta possui um custo.

**Entrada:** Grafo dirigido $\vec{G}$ com $n$ vértices e $m$ arcos, no qual cada arco $\vec{uv}$ tem um custo $C_{\vec{uv}} \geq 0$, e dois vértices $s$ (origem) e $t$ (destino).

**Saída:** $d[t]$ e um caminho mínimo de $s$ a $t$ armazenado em um vetor $anterior$ se existir.

```plaintext
Z = {s}
d[s] = 0

PARA CADA VÉRTICE v EM G:
    d[v] = ∞
    anterior[v] = 0

ENQUANTO t ∉ Z E EXISTIR ARCOS NA FRONTEIRA DE Z:
    SEJA uv UM ARCO NA FRONTEIRA DE Z TAL QUE d[v] + C_{uv} É MÍNIMO
    Z = Z ∪ {v}
    d[v] = d[u] + C_{uv}
    anterior[v] = u

DEVOLVA d[t] E anterior
```

## Algoritmo: Fleury (Trilhas de Euler)
**Descrição:** Encontra uma trilha de Euler em um grafo Euleriano $G$.

**Entrada:** Um Grafo Euleriano $G$ 

**Saída:** Uma trilha de Euler $T$ em $G$


```plaintext
T = {}

SE G POSSUI EXATAMENTE 2 VÉRTICES DE GRAU ÍMPAR:
    SEJA v UM VÉRTICE DE GRAU ÍMPAR
SENÃO:
    SEJA v UM VÉRTICE QUALQUER DE G

ENQUANTO EXISTIR ARESTA INCIDENTE EM v:
    ESCOLHA UMA ARESTA INCIDENTE EM v QUE NÃO SEJA UMA PONTE, CASO HOUVER. CASO CONTRÁRIO, ESCOLHA QUALQUER ARESTA INCIDENTE EM v.
    SEJA uv A ARESTA ESCOLHIDA
    T = T ∪ {Aresta uv}
    G = G - {Aresta uv}
    v = u
    
DEVOLVA T
```