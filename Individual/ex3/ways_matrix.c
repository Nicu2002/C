#include <stdio.h>
#include <stdlib.h>

#define graph_repr "adj_matrix.dat"
#define edges_num 20
#define nodes_num 12
#define ways_matrix_file "ways_matrix.dat"

void menu(int (*adj_matrix)[50], int (*ways_matrix)[50]);
void initialize_matrix(int (*adj_matrix)[50], int (*ways_matrix)[50]);
void view_matrix(int (*matrix)[50]);
void update_adj_matrix(int (*adj_matrix)[50], int (*ways_matrix)[50]);
void create_ways_matrix(int (*adj_matrix)[50], int (*ways_matrix)[50]);

void main() {
    int adj_matrix[50][50];
    int ways_matrix[50][50];
    initialize_matrix(adj_matrix, ways_matrix);
    menu(adj_matrix, ways_matrix);
}

void menu(int (*adj_matrix)[50], int (*ways_matrix)[50]) {
    int option;
    printf("\n---- menu ----\n");
    printf("1. Vizualizare matrice de adiacenta.\n");
    printf("2. Modificare matrice de adiacenta.\n");
    printf("3. Creare matrice a drumurilor.\n");
    printf("4. Vizualizare matrice a drumurilor.\n");
    printf("0. Exit\n");
    printf("Optiunea : ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            view_matrix(adj_matrix);
            menu(adj_matrix, ways_matrix);
            break;
        case 2:
            update_adj_matrix(adj_matrix, ways_matrix);
            break;
        case 3:
            create_ways_matrix(adj_matrix, ways_matrix);
            break;
        case 4:
            view_matrix(ways_matrix);
            menu(adj_matrix, ways_matrix);
            break;
        case 0:
            exit(1);
        default:
            printf("---- incorect input ----");
            menu(adj_matrix, ways_matrix);
            break;
    }
}

void view_matrix (int (*matrix)[50]) {
    for (int i = 0; i < nodes_num; i++) {
        printf("\n");
        for (int j = 0; j < nodes_num; j++) {
            printf(" %2d", matrix[i][j]);
        }
    }
}

void initialize_matrix(int (*adj_matrix)[50], int (*ways_matrix)[50]) {
    FILE *pf;
    pf = fopen(graph_repr, "r");

    for (int i = 0; i < nodes_num; i++) {
        for (int j = 0; j < nodes_num; j++) {
            fscanf(pf, "%d", *(adj_matrix + i) + j);
        }
    }
    fclose(pf);
    menu(adj_matrix, ways_matrix);
}

void update_adj_matrix(int (*adj_matrix)[50], int (*ways_matrix)[50]) {
    int x, y, new_value, option;
    printf("Indicate element's coordonates to change value to this or print -1 to go in main menu : \n");
    printf("\nx = ");
    scanf("%d", &x);
    if(x == -1) {
        menu(adj_matrix, ways_matrix);
    }
    printf("\ny = ");
    scanf("%d", &y);
    printf("new value (0/1/-1): ");
    scanf("%d", &new_value);
    *(*(adj_matrix + y) + x) = new_value;
    printf("\n1. New update.\n");
    printf("0. Main menu.\n");
    printf("option : ");
    scanf("%d", &option);
    if(option == 1) {
        update_adj_matrix(adj_matrix, ways_matrix);
    }
    else {
        FILE *rf;
        rf = fopen(graph_repr, "w");
        for (int i = 0; i < nodes_num; i++) {
            for (int j = 0; j < nodes_num; j++){
                fprintf(rf, "%d ", *(*(adj_matrix + i) + j));
            }
            fprintf(rf, "\n");
        }
        fclose(rf);
        menu(adj_matrix, ways_matrix);
    }
}

void create_ways_matrix(int (*adj_matrix)[50], int (*ways_matrix)[50]) {
    for (int i = 0; i < nodes_num; i++){
        for (int j = 0; j < nodes_num; j++){
            ways_matrix[i][j] = adj_matrix[i][j];
        }
    }
    for (int k = 0; k < nodes_num; k++){
        for (int i = 0; i < nodes_num; i++){
            for (int j = 0; j < nodes_num; j++){
                if (i != j && ways_matrix[i][j] == 0 && ways_matrix[i][k] == 1 && ways_matrix[k][j] == 1){
                    ways_matrix[i][j] = ways_matrix[i][k] * ways_matrix[k][j];
                }
            }
        }
    }
    FILE *pf;
    pf = fopen(ways_matrix_file, "w");

    for (int i = 0; i < nodes_num; i++) {
        for (int j = 0; j < nodes_num; j++){
            fprintf(pf, "%d ", ways_matrix[i][j]);
        }
        fprintf(pf, "\n");
    }
}