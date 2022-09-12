#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define info_file "edges.dat"
#define nodesNum 12
#define edgesNum 19

void read_edges(int (*edges)[3]);
void menu(int (*costMatrix)[nodesNum], int *minPath, int (*edges)[3]);
void createCostMatrix(int (*costMatrix)[nodesNum], int (*edges)[3]);
void createVectors(int (*costMatrix)[nodesNum], int *pathIndexes, int *nextVect);
bool vectComp(int *a, int *b);
int minNum(int *a, int (*costMatrix)[nodesNum], int nodeIndex, int *pathIndexes);
void createPath(int *minPath, int *pathIndexes, int node, int *i);
void FordAlg(int *minPath, int firstNode, int (*edges)[3]);
void createPathFord(int *minPath, int firstNode, int node, int *i, int *H, int (*edges)[3]);
void inversateVect(int *a, int i);

void main() {
    int edges[edgesNum][3], minPath[nodesNum], costMatrix[nodesNum][nodesNum];
    read_edges(edges);
    menu(costMatrix, minPath, edges);
}

void menu(int (*costMatrix)[nodesNum], int *minPath, int (*edges)[3]) {
    int firstNode, option, pathIndexes[12];
    int nextVect[nodesNum];
    for (int i = 0; i < nodesNum; i++) {
        pathIndexes[i] = 0;
        for(int j = 0; j < nodesNum; j++){
            if(i == j) {
                *(*(costMatrix + i) + j) = 0;
            }
            else{
                *(*(costMatrix + i) + j) = INT_MAX;
            }
        }
    }

    printf("\n1.Belman Kallaban for minim path.\n");
    printf("\n2.Ford for minim path.\n");
    printf("0.Exit.\n");
    printf("option : ");
    scanf("%d", &option);
    switch(option) {
        case 1:
            createCostMatrix(costMatrix, edges);
            createVectors(costMatrix, pathIndexes, nextVect);
            printf("\ninput start node : ");
            scanf("%d", &firstNode);

            minPath[0] = firstNode;
            int i = 1;
            createPath(minPath, pathIndexes, firstNode, &i);
            printf("%d ", minPath[0]);
            for (int j = 1; j < i; j++) {
                printf("-> %d ", minPath[j]);
            }
            printf("\nValoarea drumului minim : %d", *(nextVect + firstNode - 1));
            break;
        case 2:
            printf("\ninput start node : ");
            scanf("%d", &firstNode);
            FordAlg(minPath, firstNode, edges);
        case 0:
            exit(1);
    }
}

void read_edges(int (*edges)[3]) {
    FILE *pf;
    pf = fopen(info_file, "r");

    for (int i = 0; i < edgesNum; i++) {
        for (int j = 0; j < 3; j++) {
        fscanf(pf, "%d", *(edges + i) + j);
        }
    }
}

void createCostMatrix(int (*costMatrix)[nodesNum], int (*edges)[3]) {
    for (int i = 0; i < edgesNum; i++){
        int base = *(*(edges + i));
        int arrow = *(*(edges + i) + 1);
        int pond = *(*(edges + i) + 2);
        *(*(costMatrix + base - 1) + arrow - 1) = pond;
    }

    for (int i = 0; i < nodesNum; i++) {
        for (int j = 0; j < nodesNum; j++) {
            printf("%d ", *(*(costMatrix + i) + j));
        }
        printf("\n");
    }
}

void createVectors(int (*costMatrix)[nodesNum], int *pathIndexes, int *nextVect) {
    int tempVect[nodesNum];
    for (int i = 0; i < nodesNum; i++) {
        *(tempVect + i) = *(*(costMatrix + i) + nodesNum - 1);
    }
    bool condition = false;
    while(condition == false) {
        for (int i = 0; i < nodesNum; i++) {
            *(nextVect + i) = minNum(tempVect, costMatrix, i, pathIndexes);
        }
        condition = vectComp(tempVect, nextVect);
        for (int i = 0; i < nodesNum; i++){
            *(tempVect + i) = *(nextVect + i);
        }
    }

}

bool vectComp(int *a, int *b) {
    for (int i = 0; i < nodesNum; i++) {
        if(*(a + i) != *(b + i)) {
            return false;
        }
    }
    return true;
}

int minNum(int *a, int (*costMatrix)[nodesNum], int nodeIndex, int *pathIndexes) {
    int sumVect[2][nodesNum];
    int i, k;
    for (i = 0, k = 0; i < nodesNum; i++, k++) {
        if(*(a + i) != INT_MAX && *(*(costMatrix + nodeIndex) + i) != INT_MAX) {
            *(*sumVect + k) = *(a + i) + *(*(costMatrix + nodeIndex) + i);
            *(*(sumVect + 1) + k) = i;
        }
        else{
            k--;
        }
    }
    
    if(k > 0) {
        int auxMin = sumVect[0][0];
        for (int j = 1; j < k; j++) {
            if(auxMin > sumVect[0][j]){
                auxMin = sumVect[0][j];
            }
        }

        int counter = 0;
        int indexes[nodesNum];
        for (int j = 0; j < k; j ++) {
            if(auxMin == sumVect[0][j] && nodeIndex != sumVect[1][j]) {
                indexes[counter++] = sumVect[1][j];
            }
        }
        if(counter >= 1) {
            int resIndexNum = *(*(costMatrix + nodeIndex) + indexes[0]);
            *(pathIndexes + nodeIndex) = indexes[0] + 1;
            for (int j = 1; j < counter; j++) {
                if(resIndexNum > *(*(costMatrix + nodeIndex) + indexes[j])) {
                    resIndexNum = *(*(costMatrix + nodeIndex) + indexes[j]);
                    *(pathIndexes + nodeIndex) = indexes[j] + 1;
                }
            }
        }
        return auxMin;
    }
    
    return INT_MAX;
}

void createPath(int *minPath, int *pathIndexes, int node, int *i) {
    if(node != 12) {
        *(minPath + *i) = *(pathIndexes + node - 1);
        *i = *i + 1;
        createPath(minPath, pathIndexes, *(pathIndexes + node - 1), i);
    }
}

void FordAlg(int *minPath, int firstNode, int (*edges)[3]) {
    int H[nodesNum];
    for (int i = 0; i < nodesNum; i++) {
        H[i] = INT_MAX;
    }
    H[firstNode - 1] = 0;

    for (int i = 0; i < edgesNum; i++) {
        int base = edges[i][0];
        int arrow = edges[i][1];
        int pond = edges[i][2];
        int L = H[arrow - 1] - H[base - 1];

        if(L > pond) {
            H[arrow - 1] = pond + H[base - 1];
        }
    }

    int i = 1;
    *minPath = nodesNum;
    createPathFord(minPath, firstNode, 12, &i, H, edges);
    inversateVect(minPath, i);
    printf("%d ", minPath[0]);
    for (int j = 1; j < i; j++) {
        printf("-> %d ", minPath[j]);
    }
    printf("\nValoarea drumului minim : %d", H[nodesNum - 1]);
}

void createPathFord(int *minPath, int firstNode, int node, int *i, int *H, int (*edges)[3]) {
    if(node != firstNode) {
        for (int j = edgesNum - 1; j >= 0; j--) {
            if(edges[j][1] == node && *(H + node - 1) - *(H + edges[j][0] - 1) == edges[j][2]) {
                *(minPath + *i) = edges[j][0];
                goto jump;
            }
        }
        jump:
        *i = *i + 1;
        createPathFord(minPath, firstNode, *(minPath + *i - 1), i, H, edges);
    }
}

void inversateVect(int *a, int i) {
    for (int j = 0; j < i / 2; j++) {
        int temp = *(a + j);
        *(a + j) = *(a + i - 1 - j);
        *(a + i - 1 - j) = temp;
    }
}