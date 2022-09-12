#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "canalTv.h"

void readData(canal *tv, int n);
void showData(canal *tv, int n);
void clearBuffer();

void selectionSort(int n, canal *tv);
void swap(canal *a, canal *b);

void shellSort(int n, canal *tv);

void main() {
    canal *tv = NULL;
    int n;
    printf("Input chanals number : ");
    scanf("%d", &n);

    tv = (canal *)calloc(n, sizeof(canal));

    readData(tv, n);
    showData(tv, n);

    selectionSort(n, tv);
    printf("\nSortarea canalelor crescator dupa denumire : \n");
    showData(tv, n);

    shellSort(n, tv);
    printf("\nSortarea canalelor descrescator dupa rating : \n");
    showData(tv, n);
}

void readData(canal *tv, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n---Read data for chanel #%d ---", i + 1);
        clearBuffer();
        printf("\nname : ");  scanf("%[^\n]%*c", (tv + i)->name);
        printf("\ncountry : ");  scanf("%[^\n]%*c", (tv + i)->country);
        printf("\nphone : ");  scanf("%[^\n]%*c", (tv + i)->phone);
        printf("\ntype : ");  scanf("%[^\n]%*c", (tv + i)->type);
        printf("\nrating : ");  scanf("%d", &(tv + i)->rating);
    }
}

void showData(canal *tv, int n) {
    printf("\n---Show data---\n");
    for (int i = 0; i < n; i++) {
        printf("%s | %s | %s | %s | %d\n", (tv + i)->name, (tv + i)->country, (tv + i)->phone, (tv + i)->type, (tv + i)->rating);
    }
}

void clearBuffer() {
    char c;
    do{
        c = getchar();
    } while (c != '\n');
}

void selectionSort(int n, canal *tv) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if(strcmp((tv + i)->name, (tv + j)->name) > 0) {
                swap(tv + i, tv + j);
            }
        }
    }
}

void swap(canal *a, canal *b) {
    canal temp = *a;
    *a = *b;
    *b = temp;
}

void shellSort(int n, canal *tv) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++){
            canal temp = *(tv + i);
            int j;
            for (j = i; j >= gap && (tv + j - gap)->rating < temp.rating; j -= gap) {
                *(tv + j) = *(tv + j - gap);
            }
            *(tv + j) = temp;
        }
    }
}

