#include <stdio.h>

// De modificat doar ce tine de #define !
#define nodes_num 13 // numarul de varfuri
#define edges_num 20 // numarul de muchii / arce
#define file_name "edges_matrix.dat" // fisierul cu lista de muchii (fiecare muchie de forma 'a b' din rand nou)
#define graph_type "orientat" // tipul grafului (orientat / neorientat)
#define result_file_orientat "incidence_matrix_or.dat" // fisierul de salvare a matricii pentru graf orientat
#define result_file_neorientat "incidence_matrix_neor.dat" // fisierul de salvare a matricii pentru graf neorientat

void read_edges(int rows, int columns, int (*edges)[2]);
void print_matrix(int (*matrix)[edges_num + 1], int (*edges)[2]);
void save_matrix(int rows, int columns, int (*incidence_matrix)[edges_num + 1]);
void create_matrix_incidence(int rows, int columns, int (*edges)[2], int (*incidence_matrix)[edges_num + 1]);

void main() {
    int incidence_matrix[nodes_num + 1][edges_num + 1];
    int edges[edges_num][2];

    read_edges(edges_num, 2, edges);
    create_matrix_incidence(nodes_num + 1, edges_num + 1, edges, incidence_matrix);
    print_matrix(incidence_matrix, edges);
    save_matrix(nodes_num + 1, edges_num + 1, incidence_matrix);
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

void create_matrix_incidence(int rows, int columns, int (*edges)[2], int (*incidence_matrix)[edges_num + 1]) {
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns;j++){
            incidence_matrix[i][j] = 0;
        }
    }
    for (int i = 0, k = 1; i < edges_num + 1; i++, k++){
        int base = edges[i][0];
        int arrow = edges[i][1];

        if(graph_type == "orientat") {
            incidence_matrix[base][k] = -1;
            incidence_matrix[arrow][k] = 1;
        }
        else {
            incidence_matrix[base][k] = 1;
            incidence_matrix[arrow][k] = 1;
        }
    }
}

void print_matrix(int (*matrix)[edges_num + 1], int (*edges)[2]) {
    printf("arcele/muchiile luate la rand pentru matrice : \n");
    for (int i = 0; i < edges_num ; i++){
        printf(" |%d,%d|", edges[i][0], edges[i][1]);
    }
    for (int i = 1; i < nodes_num + 1; i++){
            printf("\n");
            for (int j = 1; j < edges_num + 1; j++){
                printf("  %2d", *(*(matrix + i) + j));
            }
        }
}

void save_matrix(int rows, int columns, int (*matrix)[edges_num + 1]) {
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
