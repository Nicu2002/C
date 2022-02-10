#include <stdio.h>

// De modificat doar ce tine de #define !
#define nodes_num 12 // numarul de varfuri
#define edges_num 20 // numarul de muchii / arce
#define file_name "oriented_edges.dat" // fisierul cu lista de muchii (fiecare muchie de forma 'a b' din rand nou)
#define graph_type "orientat" // tipul grafului (orientat / neorientat)
#define result_file_orientat "adjacence_matrix_or.dat" // fisierul de salvare a matricii pentru graf orientat
#define result_file_neorientat "adjacence_matrix_neor.dat" // fisierul de salvare a matricii pentru graf neorientat

void read_edges(int rows, int columns, int (*edges)[2]);
void print_matrix(int (*matrix)[nodes_num + 1], int (*edges)[2]);
void save_matrix(int rows, int columns, int (*adjacence_matrix)[nodes_num + 1]);
void create_matrix_adjacence(int rows, int columns, int (*edges)[2], int (*adjacence_matrix)[nodes_num + 1]);

void main() {
    int adjacence_matrix[nodes_num + 1][nodes_num + 1];
    int edges[edges_num][2];

    read_edges(edges_num, 2, edges);
    create_matrix_adjacence(nodes_num + 1, nodes_num + 1, edges, adjacence_matrix);
    print_matrix(adjacence_matrix, edges);
    save_matrix(nodes_num + 1, nodes_num + 1, adjacence_matrix);
}

// Read file with edges and create edges matrix :
void read_edges(int rows, int columns, int (*edges)[2]){
    FILE *pf;
    pf = fopen(file_name, "r");
    if(pf == NULL) {
        printf("file is empty");
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++) {
            fscanf(pf, "%d", *(edges + i) + j);
        }
    }
    fclose(pf);
}

void create_matrix_adjacence(int rows, int columns, int (*edges)[2], int (*adjacence_matrix)[nodes_num + 1]) {
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns;j++){
            adjacence_matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < edges_num + 1; i++){
        int base = edges[i][0];
        int arrow = edges[i][1];

        if(graph_type == "orientat") {
            adjacence_matrix[base][arrow] = 1;
        }
        else {
            adjacence_matrix[base][arrow] = 1;
            adjacence_matrix[arrow][base] = 1;
        }
    }
}

void print_matrix(int (*matrix)[nodes_num + 1], int (*edges)[2]) {
    printf("arcele/muchiile luate la rand pentru matrice : \n");
    for (int i = 0; i < edges_num ; i++){
        printf(" |%d,%d|", edges[i][0], edges[i][1]);
    }
    for (int i = 1; i < nodes_num + 1; i++){
            printf("\n");
            for (int j = 1; j < nodes_num + 1; j++){
                printf("  %2d", *(*(matrix + i) + j));
            }
        }
}

void save_matrix(int rows, int columns, int (*matrix)[nodes_num + 1]) {
    FILE *pf;
    if(graph_type == "orientat") {
        pf = fopen(result_file_orientat, "w");
    }
    else {
        pf = fopen(result_file_neorientat, "w");
    }

    for (int i = 1; i < rows; i++){
        for (int j = 1; j < columns; j++) {
            fprintf(pf, " %2d ", matrix[i][j]);
        }
        fprintf(pf, "\n");
    }
    fclose(pf);
}
