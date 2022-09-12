#include <stdio.h>
#include <string.h>

typedef struct Carte {
    char denumire[20];
    int price;
} carte;

void readInfo(carte *librarie, int n);
void showInfo(carte *librarie, int n);
void selectionSort(carte *librarie, int n);
void swap(carte *a, carte *b);

void main() {
    carte librarie[5];
    int n;
    printf("input n :");
    scanf("%d", &n);

    readInfo(librarie, n);
    showInfo(librarie, n);
    selectionSort(librarie, n);
    printf("\nDupa sortarea dupa pret\n");
    showInfo(librarie, n);
}

void readInfo (carte *librarie, int n) {
    for (int i = 0; i < n; i++) {
        printf("Input book name : ");
        scanf("%s", (librarie + i)->denumire);
        printf("Input book price : ");
        scanf("%d", &(librarie + i)->price);
    }
}

void showInfo(carte *librarie, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nbook %d name : %s", i + 1, (librarie + i)->denumire);
        printf("\nbook %d price : %d", i + 1, (librarie + i)->price);
    }
}

void selectionSort(carte *librarie, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if((librarie + i)->price > (librarie + j)->price){
                swap(librarie + i, librarie + j);
            }
        }
    }
}

void swap(carte *a, carte *b) {
    carte temp = *a;
    *a = *b;
    *b = temp;
}