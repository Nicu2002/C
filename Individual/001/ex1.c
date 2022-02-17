#include <stdio.h>

#define graph_repr "graph_repr.dat"
#define nodes_num 11
#define edges_num 19

void read_edges(int (*edges)[2]);
void create_adjacency_matrix(int (*edges)[2], int (*adjacency_matrix)[nodes_num]);
void create_path_matrix(int (*adjacency_matrix)[nodes_num], int (*paths_matrix)[nodes_num]);
void create_hamilton_path(int (*paths_matrix)[nodes_num], int (*hamilton_path)[2]);
void swap(int *a, int *b);

void main() {
  int edges[edges_num][2], adjacency_matrix[nodes_num][nodes_num], paths_matrix[nodes_num][nodes_num];
  int hamilton_path[nodes_num][2];

  printf("--------------------------------");
  read_edges(edges);
  printf("\n----Matricea de adiacenta :\n");
  create_adjacency_matrix(edges, adjacency_matrix);
  printf("\n----Matricea drumurilor\n");
  create_path_matrix(adjacency_matrix, paths_matrix);
  printf("\nDrumul hamilton\n");
  create_hamilton_path(paths_matrix, hamilton_path);
  printf("\n--------------------------------");
}

void read_edges(int (*edges)[2]) {
  FILE *pf;
  pf = fopen(graph_repr, "r");

  for (int i = 0; i < edges_num; i++) {
    for (int j = 0; j < 2; j++) {
      fscanf(pf, "%d", *(edges + i) + j);
    }
  }
}

void create_adjacency_matrix(int (*edges)[2], int (*adjacency_matrix)[nodes_num]) {
  for (int i = 0; i < nodes_num; i++){
    for (int j = 0; j < nodes_num; j++){
      adjacency_matrix[i][j] = 0;
    }
  }
  for (int i = 0; i < edges_num; i++){
    int base = edges[i][0];
    int arrow = edges[i][1];

    adjacency_matrix[base - 1][arrow - 1] = 1;
  }
  for (int i = 0; i < nodes_num; i++){
    for (int j = 0; j < nodes_num;j++){
      printf("%d ", *(*(adjacency_matrix + i) + j));
    }
    printf("\n");
  }
}

void create_path_matrix(int (*adjacency_matrix)[nodes_num], int (*paths_matrix)[nodes_num]) {
  for (int i = 0; i < nodes_num; i++){
    for (int j = 0; j < nodes_num; j++){
      paths_matrix[i][j] = adjacency_matrix[i][j];
    }
  }
  for (int k = 0; k < nodes_num; k++){
    for (int i = 0; i < nodes_num; i++){
      for (int j = 0; j < nodes_num; j++){
        if (i != j && paths_matrix[i][j] == 0 && paths_matrix[i][k] == 1 && paths_matrix[k][j] == 1){
          paths_matrix[i][j] = paths_matrix[i][k] * paths_matrix[k][j];
        }
      }
    }
  }
  for (int i = 0; i < nodes_num; i++){
    for (int j = 0; j < nodes_num;j++){
      printf("%d ", *(*(paths_matrix + i) + j));
    }
    printf("\n");
  }
}

void create_hamilton_path(int (*paths_matrix)[nodes_num], int (*hamilton_path)[2]) {
  int sum = 0;
  for (int i = 0; i < nodes_num; i++){
    *(*(hamilton_path + i)) = i + 1;
  }
  for (int i = 0; i < nodes_num; i++) {
    int counter = 0;
    for (int j = 0; j < nodes_num; j++){
      if(*(*(paths_matrix + i) + j) == 1) {
        counter++;
      }
    }
    *(*(hamilton_path + i) + 1) = counter;
    sum += counter;
  }

  if(sum == nodes_num *(nodes_num - 1) / 2) {
    for (int i = 0; i < nodes_num - 1; i++) {
      for (int j = i + 1; j < nodes_num; j++) {
        if(*(*(hamilton_path + i) + 1) < *(*(hamilton_path + j) + 1)) {
          swap(*(hamilton_path + i) + 1, *(hamilton_path + j) + 1);
          swap(*(hamilton_path + i), *(hamilton_path + j));
        }
      }
    }
    for (int i = 0; i < nodes_num; i++){
      printf("%d ", *(*(hamilton_path + i)));
    } 
  }
  else {
    printf("Nu este drum hamiltonian !");
  }
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}