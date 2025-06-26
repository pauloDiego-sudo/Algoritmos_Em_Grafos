# Algoritmos em Grafos

Este repositório contém implementações de diversos algoritmos em grafos que estou aprendendo na disciplina de Grafos. O objetivo é praticar e documentar os diferentes algoritmos e suas aplicações.

## Sobre o Projeto

Este projeto foi criado como parte dos estudos da disciplina de Grafos, onde estou aprendendo sobre diferentes algoritmos e suas implementações. Cada algoritmo será implementado e documentado com exemplos práticos.

## Estrutura de Dados usada

Para a implementação dos algoritmos, foi utilizada a estrutura de dados de Lista de Adjacências, que consiste em um array de listas, onde cada índice representa um vértice do grafo e sua lista contém os vértices adjacentes a ele. Esta estrutura é eficiente para grafos esparsos e permite uma fácil iteração sobre os vizinhos de cada vértice.

## Algoritmos Implementados

- [x] Verificação de Grafo Conexo
- [x] Quantidade de Vértices em Componente Conexa
- [x] Quantidade de Componentes Conexas
- [x] Verificação de Grafo k-Aresta-Conexo
- [x] Verificação de Grafo k-Vértice-Conexo
- [x] Verificação de Floresta
- [x] Algoritmo de Kruskal- Árvore Geradora Minima
- [x] Algoritmo de Prim - Árvore Geradora Minima
- [x] Algoritmo de Dijkstra em C - Caminho mínimo em grafos dirigidos

## Em Breve
- [O] Algoritmo de Fleury - Trilhas de Euler

## Como buildar
### Windows
1. Instale o CMake e o compilador C/C++ (como MinGW).
2. Abra o terminal na pasta raiz do projeto.
3. Execute o script `build.bat` para compilar o projeto.
### Linux
1. Instale o CMake e o compilador C/C++ (como g++).
2. Abra o terminal na pasta raiz do projeto.
3. Crie uma pasta `build` e entre nela:
   ```bash
   mkdir build && cd build
   ```
4. Especifique o seu compilador C/C++:
   ```bash
   cmake -G "Unix Makefiles" ..
   ```
5. Compile o projeto:
   ```bash
    cmake --build .
   ```
## Como Executar
Após compilar o projeto, você pode executar os exemplos de uso dos algoritmos. Cada algoritmo possui um exemplo específico que pode ser encontrado na pasta `data/input`. O comando para executar o programa é:

```bash
graph.exe <input_file_path> <weigthed?_true_or_false>
```

## Tecnologias Utilizadas

- C, C++, CMake

## Contribuições

Este é um projeto pessoal para fins de estudo, mas sugestões e correções são bem-vindas!

