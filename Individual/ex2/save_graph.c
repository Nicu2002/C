#include <stdio.h>
#include <stdlib.h>

#define graph_repr "matrix.dat"
#define graph_type "orientat"
#define edges_num 26
#define nodes_num 14

void menu(int *cols, int (*matrix)[50]);
void initialize_matrix(int *cols, int (*matrix)[50]);
void change_type(int *cols, int (*matrix)[50]);
void view_matrix(int *cols, int (*matrix)[50]);
void update_matrix(int *cols, int (*matrix)[50]);

void main() {
    int matrix[30][50];
    int cols;
    change_type(&cols, matrix);
}

void change_type(int *cols, int (*matrix)[50]) {
    int matrix_type;
    printf("Introduceti tipul reprezentarii(tipul matricii de input)\n");
    printf("1. Matrice de incidenta\n");
    printf("2. Matrice de adiacenta\n");
    printf("0. Exit program\n");
    printf("Optiunea :");
    scanf("%d", &matrix_type);
    if(matrix_type == 0) {
        exit(1);
    }
    else if (matrix_type != 1 && matrix_type != 2) {
        printf("\n---- incorect input ----");
        change_type(cols, matrix);
    }
    else if (matrix_type == 1){
        *cols = edges_num;
    }
    else {
        *cols = nodes_num;
    }
    initialize_matrix(cols, matrix);
    menu(cols, matrix);
}

void menu(int *cols, int (*matrix)[50]) {
    int option;
    printf("\n---- menu ----\n");
    printf("1. Schimbarea tipului reprezentarii(tipul matricii de input)\n");
    printf("2. Vizualizare matrice\n");
    printf("3. Modificare matrice\n");
    printf("0. Exit\n");
    printf("Optiunea : ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            change_type(cols, matrix);
            break;
        case 2:
            view_matrix(cols, matrix);
            menu(cols, matrix);
            break;
        case 3:
            update_matrix(cols, matrix);
            break;
        case 0:
            exit(1);
        default:
            printf("---- incorect input ----");
            menu(cols, matrix);
            break;
    }
}

void view_matrix (int *cols, int (*matrix)[50]) {
    for (int i = 0; i < nodes_num; i++) {
        printf("\n");
        for (int j = 0; j < *cols; j++) {
            printf(" %2d", matrix[i][j]);
        }
    }
}

void initialize_matrix(int *cols, int (*matrix)[50]) {
    // matrix = malloc(nodes_num * sizeof(int));
    // for (int i = 0; i < *cols; i++) {
    //     matrix[i] = calloc(*cols, sizeof(int));
    // }
    FILE *pf;
    pf = fopen(graph_repr, "r");

    for (int i = 0; i < nodes_num; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(pf, "%d", *(matrix + i) + j);
        }
    }
    fclose(pf);
    menu(cols, matrix);
}

void update_matrix(int *cols, int (*matrix)[50]) {
    int x, y, new_value, option;
    printf("Indicate element's coordonates to change value to this or print -1 to go in main menu : \n");
    printf("\nx = ");
    scanf("%d", &x);
    if(x == -1) {
        menu(cols, matrix);
    }
    printf("\ny = ");
    scanf("%d", &y);
    printf("new value (0/1/-1): ");
    scanf("%d", &new_value);
    *(*(matrix + y) + x) = new_value;

    printf("\n1. New update.\n");
    printf("0. Main menu.\n");
    printf("option : ");
    scanf("%d", &option);

    if(option == 1) {
        update_matrix(cols, matrix);
    }
    else {
        FILE *rf;
        rf = fopen(graph_repr, "w");
        for (int i = 0; i < nodes_num; i++) {
            for (int j = 0; j < *cols; j++){
                fprintf(rf, "%d ", *(*(matrix + i) + j));
            }
            fprintf(rf, "\n");
        }
        fclose(rf);
        menu(cols, matrix);
    }
}