#include <stdio.h>

#define edges_file "edges.dat"
#define edges_num 20
#define nodes_num 12
#define res_file "adj_matrix.dat"

void create_matrix(int (*matrix)[nodes_num + 1], int (*edges_matrix)[2]);
void view_matrix(int (*matrix)[nodes_num + 1]);
void read_edges(int (*edges)[2]);

void main() {
    int matrix[nodes_num + 1][nodes_num + 1];
    int edges_matrix[edges_num][2];

    create_matrix(matrix, edges_matrix);
    view_matrix(matrix);
}

void create_matrix(int (*matrix)[nodes_num + 1], int (*edges_matrix)[2]) {
    read_edges(edges_matrix);

    for (int i = 0; i < nodes_num + 1; i++) {
        for (int j = 0; j < nodes_num + 1; j++) {
            matrix[i][j] = 0;
        }
    }
    
    for (int i = 0; i < edges_num; i++) {
        int x = edges_matrix[i][0];
        int y = edges_matrix[i][1];

        matrix[x][y] = 1;
    }
    FILE *mat_file;
    mat_file = fopen(res_file, "w");

    for (int i = 1; i < nodes_num + 1; i++) {
        for (int j = 1; j < nodes_num + 1; j++) {
            fprintf(mat_file, "%d ", matrix[i][j]);
        }
        fprintf(mat_file, "\n");
    }
    fclose(mat_file);
}

void view_matrix(int (*matrix)[nodes_num + 1]) {
    for (int i = 1; i < nodes_num + 1; i++){
        printf("\n");
        for (int j = 1; j < nodes_num + 1; j++){
            printf("%d ", matrix[i][j]);
        }
    }
}

void read_edges(int (*edges)[2]){
    FILE *pf;
    pf = fopen(edges_file, "r");
    if(pf == NULL) {
        printf("file is empty");
    }

    for (int i = 0; i < edges_num; i++){
        for (int j = 0; j < 2; j++) {
            fscanf(pf, "%d", *(edges + i) + j);
        }
    }
    fclose(pf);
}