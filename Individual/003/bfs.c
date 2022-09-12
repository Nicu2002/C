#include <stdio.h>
#include <stdlib.h>

#define graph_repr "graph_repr.dat"
#define nodes_num 11
#define edges_num 16

void read_edges(int (*edges)[2]);
void create_adjacency_matrix(int (*edges)[2], int (*adjacency_matrix)[nodes_num]);
void menu(int (*adjacency_matrix)[nodes_num], int *path, int *counter);
void BF(int start, int *node_status, int (*adjacency_matrix)[nodes_num]);

void main() {
    int edges[edges_num][2], adjacency_matrix[nodes_num][nodes_num], path[nodes_num], counter = 0;
    read_edges(edges);
    create_adjacency_matrix(edges, adjacency_matrix);
    menu(adjacency_matrix, path, &counter);
}

void menu(int (*adjacency_matrix)[nodes_num], int *path, int *counter) {
    int nodes_status[nodes_num], first_node, option;
    for (int i = 0; i < nodes_num; i++) {
    	nodes_status[i] = 0;
	    path[i] = 0;
    }

    printf("\n1.Give first node.\n");
    printf("0.Exit.\n");
    printf("option : ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            printf("input start node : ");
            scanf("%d", &first_node);

            BF(first_node, nodes_status, adjacency_matrix);
            break;
        case 0:
            exit(1);
    }
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
        adjacency_matrix[arrow - 1][base - 1] = 1;
    }
    for (int i = 0; i < nodes_num; i++){
        for (int j = 0; j < nodes_num;j++){
            printf("%d ", *(*(adjacency_matrix + i) + j));
        }
        printf("\n");
    }
}

void BF(int start, int *node_status, int (*adjacency_matrix)[nodes_num]) {
    int analised_num, visited_num, i, nod, queue[nodes_num];
    analised_num = 0;
    visited_num = 0;
    node_status[start - 1]=1; 
    queue[analised_num]=start;
    printf("%d", start);
    while(analised_num <= visited_num){
        nod = queue[analised_num];
        for(i = 0; i < nodes_num; i++){
            if( adjacency_matrix[nod - 1][i]==1 && node_status[i]==0 ) { // caz favorabil
                visited_num++; 
                queue[visited_num] = i + 1;
                printf(" -> %d", i + 1); // print nod vizitat
                node_status[i] = 1;
            }
        }
        analised_num++;
    }
}t