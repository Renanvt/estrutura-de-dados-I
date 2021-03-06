/** dfs.c
 * @author Arthur Xavier <arthur.xavierx@gmail.com>
 * @usage 
 *   $ gcc dfs.c
 *   $ ./a.out < maze1.txt
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Algoritmo de Busca em Profundidade
 * (Depth-First Search)
 *
 * Este algoritmo realiza uma busca percorrendo todo um grafo
 * em sua profundidade, isto é, para cada vértice do grafo,
 * percorre todos os seus vértices adjacentes recursivamente
 * Implementado aqui de maneira a buscar por um vértice 'goal'
 * 
 * A matriz de adjacência do grafo é dada no formato:
 *
 * N           -> N = quantidade de vértices do grafo
 * X1 [adj[1]]
 * ...
 * Xi [adj[i]] ->  Xi   = quantidade de vértices adjacentes ao vértice i
 * ...           adj[i] = lista de vértices adjacentes ao vértice i
 * XN [adj[N]]
 *
 * O algoritmo funciona da seguinte forma (sem guardar o caminho percorrido):
 * -> Partindo de um vértice V
 *  ? V é o vértice de destino?
 *   +S -> Termina a busca
 *   -N -> Para cada vértice i adjacente ao vértice V
 *        -> Realiza a busca no vértice i
 *
 * @param graph Matriz de adjacencia do grafo
 * @param node Vertice de origem da busca
 * @param goal Objetivo da busca
 * @param path Array que guarda o caminho percorrido pela busca
 * @param path_size Tamanho atual do array path
 *
 * @return Retorna o Vertice objetivo da busca se esta o atingiu
 */
int dfs(int** graph, int node, int goal, int* path, size_t* path_size) {
  size_t i, size;
  int v;
  // se a busca atingiu o vértice de destino, retorna este
  if(node == goal) {
    return goal;

  // caso contrário, realiza a busca nos vértices adjacentes
  } else {

    // [
    // armazena a quantidade de vértices conectados ao vértice atual
    size = graph[node][0];
    // elimina o vértice atual da busca para que este 
    // não volte a ser buscado novamente - elimina recursão infinita
    graph[node][0] = 0;
    // ]

    // para cada vértice v adjacente ->
    for(i = 1; i <= size; i++) {
      // se a busca no vértice adjacente atingiu o destino,
      // insere o vértice atual no caminho percorrido
      // e retorna o vértice de destino para que os níveis superiores
      // da recursão saibam que a busca foi concluída
      if(dfs(graph, graph[node][i], goal, path, path_size) == goal) {

        // path[*path_size] = node;
        // *path_size = *path_size + 1;
        // ^
        path[(*path_size)++] = node;

        return goal;
      }
    }
  }
} 

//
int main() {
  // variáveis de iteração
  size_t i, j;
  // @var n linhas da matriz de adjacência - vértices do grafo
  // @var v variável temporária - colunas da matriz
  size_t n, v;
  // matriz de adjacência
  int** matrix;
  // caminho percorrido pela busca
  int* path;
  size_t path_size = 0;

  // lê a quantidade de vértices do grafo
  scanf("%lu", &n);
  // aloca a matriz de adjacência
  matrix = (int**)malloc(sizeof(int*)*(n + 1));
  // aloca espaço suficiente para o caminho no pior caso (n+1)
  path = (int*)malloc(sizeof(int*)*(n + 1));

  for(i = 0; i < n + 1; i++) {
    // lê a quantidade de conexões do vértice i
    scanf("%lu", &v);
    // aloca, na linha i da matriz, v colunas
    matrix[i] = (int*)malloc(sizeof(int)*v + 1);
    // insere na coluna 0 a quantidade de conexões do vértice i
    matrix[i][0] = v;

    // lê os vértices conectados ao vértice i e insere-os na matriz
    for(j = 1; j <= v; j++)
      scanf("%d", matrix[i] + j);
  }

  // insere o vértice de origem da busca no caminho
  path[path_size++] = 0;
  // realiza a busca
  if(dfs(matrix, n, 0, path, &path_size) == 0) {
    // caso a busca tenha encontrado o vértice objetivo,
    // imprime o caminho
    for(i = 0; i < path_size; i++)
      printf("%d ", path[i]);
  } else {
    // caso contrário, imprime uma mensagem de erro
    fprintf(stderr, "This maze has no solution");
    return 1;
  }
  
  // desaloca a memória utilizada pela matriz e pelo array path
  free(matrix);
  free(path);

  printf("\n");

  return 0;
}
