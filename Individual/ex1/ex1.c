#include <stdio.h>

void create_matrix(int edges, int nodes, int (*adj_matrix)[13], int (*edges_arr)[2]);
void print_matrix(int nodes, int (*adj_matrix)[13]);

void main() {
    int edges = 20, nodes = 12, adj_matrix[13][13];
    int edges_arr[20][2] = {{1, 3}, {1, 6}, {2, 1}, {3, 2}, {3, 4}, 
                            {3, 6}, {4, 8}, {4, 9}, {5, 4}, {5, 7}, 
                            {5, 9}, {6, 5}, {6, 7}, {7, 10}, {8, 11},
                            {9, 8}, {9, 12}, {11, 9}, {11, 12}, {12, 10}};

    create_matrix(edges, nodes, adj_matrix, edges_arr);
}

void create_matrix(int edges, int nodes, int (*adj_matrix)[13], int (*edges_arr)[2]) {
    for (int i = 0; i < nodes + 1;i++){
        for (int j = 0; j < nodes + 1;j++){
            *(*(adj_matrix + i) + j) = 0;
        }
    }

    for (int i = 0; i < edges; i++){
        int x = edges_arr[i][0];
        int y = edges_arr[i][1];

        adj_matrix[x][y] = 1;
    }
    print_matrix(nodes, adj_matrix);
}

void print_matrix(int nodes, int (*adj_matrix)[13]) {
    for (int i = 1; i < nodes + 1;i++){
        for (int j = 1; j < nodes + 1;j++){
            printf("%d ", *(*(adj_matrix + i) + j));
        }
        printf("\n");
    }
}