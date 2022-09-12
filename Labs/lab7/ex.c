#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

struct Cost {
    int lowPrice;
    int avgPrice;
    int highPrice;
};

typedef struct Cinematograf{
    char denumirea[20];
    char adresa[30];
    char telefonul[20];
    int numarLocuri;
    struct Cost priceList;
}cinema;

void completeFile(cinema *cityCinemas, int n);
void menu(int n, cinema *cityCinemas);
void ShowData(int n, cinema *cityCinemas);
void addNewStructure(int *n, cinema *cityCinemas);
void modificate(int *n, cinema *cityCinemas);
void updateFile(int *n, cinema *cityCinemas);
void sortAvgPrice(int n, cinema *cityCinemas);
void sortDenumire(int n, cinema *cityCinemas);
void removeStruct(int *n, cinema *cityCinemas);

void main() {
    int n;
    printf("input n :");
    scanf("%d", &n);
    cinema *cityCinemas;
    cityCinemas = (cinema *)calloc(n, sizeof(cinema));
    menu(n, cityCinemas);
}

//completarea fisierului cu ajutorul programului 
void completeFile(cinema *cityCinemas, int n) {
    FILE *pf;
    pf = fopen("file.txt", "w");
    for (int i = 0; i < n; i++) {
        printf("--- cinema %d ---\n", i + 1);
        printf("Denumirea : ");
        fflush(stdin);
        scanf("%s", (cityCinemas + i)->denumirea);
        fprintf(pf, "%s ", (cityCinemas + i)->denumirea);
        
        printf("Adresa : ");
        scanf("%s", (cityCinemas + i)->adresa);
        fprintf(pf, "%s ", (cityCinemas + i)->adresa);

        printf("Telefonul : ");
        scanf("%s", (cityCinemas + i)->telefonul);
        fprintf(pf, "%s ", (cityCinemas + i)->telefonul);

        printf("Numar locuri : ");
        scanf("%d", &(cityCinemas + i)->numarLocuri);
        fprintf(pf, "%d ", (cityCinemas + i)->numarLocuri);

        printf("Pret ieftit : ");
        scanf("%d", &(cityCinemas + i)->priceList.lowPrice);
        fprintf(pf, "%d ", (cityCinemas + i)->priceList.lowPrice);

        printf("Pret mediu : ");
        scanf("%d", &(cityCinemas + i)->priceList.avgPrice);
        fprintf(pf, "%d ", (cityCinemas + i)->priceList.avgPrice);

        printf("Pret scump : ");
        scanf("%d", &(cityCinemas + i)->priceList.highPrice);
        fprintf(pf, "%d\n", (cityCinemas + i)->priceList.highPrice);

    }
    fclose(pf);
}

void menu(int n, cinema *cityCinemas) {
    printf("\n--- menu ---\n");
    printf("1) Completarea fisierului initial.\n");
    printf("2) Afisarea elementelor din fisier la ecran.\n");
    printf("3) Adaugarea unei structuri noi la sfarsitul fisierului.\n");
    printf("4) Modificarea structurii dupa numarul de locuri.\n");
    printf("5) Sortarea structurilor dupa pretul mediu.\n");
    printf("6) Sortarea structurilor dupa alfabet.\n");
    printf("7) Eliminarea unei structuri din fisier.\n");
    printf("0) Exit.\n");

    int option;
    printf("Optiunea : ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            completeFile(cityCinemas, n);
            menu(n, cityCinemas);
            break;
        case 2:
            ShowData(n, cityCinemas);
            menu(n, cityCinemas);
            break;
        case 3:
            addNewStructure(&n, cityCinemas);
            break;
        case 4:
            modificate(&n, cityCinemas);
            menu(n, cityCinemas);
            break;
        case 5:
            sortAvgPrice(n, cityCinemas);
            updateFile(&n, cityCinemas);
            menu(n, cityCinemas);
            break;
        case 6:
            sortDenumire(n, cityCinemas);
            updateFile(&n, cityCinemas);
            menu(n, cityCinemas);
            break;
        case 7:
            removeStruct(&n, cityCinemas);
            updateFile(&n, cityCinemas);
            menu(n, cityCinemas);
            break;
        case 0:
            exit(1);
            break;
    }
}

void ShowData(int n, cinema *cityCinemas) {
    for (int i = 0; i < n; i++) {
        printf("\n--- cinema %d ---", i + 1);
        printf("\ndenumirea : %s", (cityCinemas + i)->denumirea);
        printf("\nadresa : %s", (cityCinemas + i)->adresa);
        printf("\ntelefonul : %s", (cityCinemas + i)->telefonul);
        printf("\nnumarul de locuri : %d", (cityCinemas + i)->numarLocuri);
        printf("\npret low : %d", (cityCinemas + i)->priceList.lowPrice);
        printf("\npret average : %d", (cityCinemas + i)->priceList.avgPrice);
        printf("\npret high : %d", (cityCinemas + i)->priceList.highPrice);
    }
}

void addNewStructure(int *n, cinema *cityCinemas) {
    *n = *n + 1;
    cityCinemas = (cinema *)realloc(cityCinemas, *n * sizeof(cinema));
    FILE *pf;
    pf = fopen("file.txt", "a");
    printf("\n--- Adaugare structura noua ---");

    printf("Denumirea : ");
    fflush(stdin);
    scanf("%s", (cityCinemas + *n - 1)->denumirea);
    fseek(pf, sizeof(cinema) * (*n - 2), SEEK_END);
    fprintf(pf, "%s ", (cityCinemas + *n - 1)->denumirea);

    printf("Adresa : ");
    scanf("%s", (cityCinemas + *n - 1)->adresa);
    fseek(pf, sizeof(cinema) * (*n - 2), SEEK_END);
    fprintf(pf, "%s ", (cityCinemas + *n - 1)->adresa);

    printf("Telefonul : ");
    scanf("%s", (cityCinemas + *n - 1)->telefonul);
    fseek(pf, sizeof(cinema) * (*n - 2), SEEK_END);
    fprintf(pf, "%s ", (cityCinemas + *n - 1)->telefonul);

    printf("Numar locuri : ");
    scanf("%d", &(cityCinemas + *n - 1)->numarLocuri);
    fseek(pf, sizeof(cinema) * (*n - 2), SEEK_END);
    fprintf(pf, "%d ", (cityCinemas + *n - 1)->numarLocuri);

    printf("Pret ieftit : ");
    scanf("%d", &(cityCinemas + *n - 1)->priceList.lowPrice);
    fseek(pf, sizeof(cinema) * (*n - 2), SEEK_END);
    fprintf(pf, "%d ", (cityCinemas + *n - 1)->priceList.lowPrice);

    printf("Pret mediu : ");
    scanf("%d", &(cityCinemas + *n - 1)->priceList.avgPrice);
    fseek(pf, sizeof(cinema) * (*n - 2), SEEK_END);
    fprintf(pf, "%d ", (cityCinemas + *n - 1)->priceList.avgPrice);

    printf("Pret scump : ");
    scanf("%d", &(cityCinemas + *n - 1)->priceList.highPrice);
    fseek(pf, sizeof(cinema) * (*n - 2), SEEK_END);
    fprintf(pf, "%d\n", (cityCinemas + *n - 1)->priceList.highPrice);

    fclose(pf);
    menu(*n, cityCinemas);
}

// modificarea structurilor, inclusiv in fisier (denumirea cu majuscule)
void modificate(int *n, cinema *cityCinemas) {
    for (int i = 0; i < *n; i++) {
        if(((cityCinemas + i)->denumirea)[0] != toupper((cityCinemas + i)->denumirea[0])) {

            (cityCinemas + i)->denumirea[0] = toupper((cityCinemas + i)->denumirea[0]);
        }
    }
    updateFile(n, cityCinemas);
}

void updateFile(int *n, cinema *cityCinemas) {
    FILE *pf;
    pf = fopen("file.txt", "w");

    for (int i = 0; i < *n; i++) {
        fprintf(pf, "%s ", (cityCinemas + i)->denumirea);
        fprintf(pf, "%s ", (cityCinemas + i)->adresa);
        fprintf(pf, "%s ", (cityCinemas + i)->telefonul);
        fprintf(pf, "%d ", (cityCinemas + i)->numarLocuri);
        fprintf(pf, "%d ", (cityCinemas + i)->priceList.lowPrice);
        fprintf(pf, "%d ", (cityCinemas + i)->priceList.avgPrice);
        fprintf(pf, "%d\n", (cityCinemas + i)->priceList.highPrice);
    }

    fclose(pf);
}

void sortAvgPrice(int n, cinema *cityCinemas) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if((cityCinemas + i)->priceList.avgPrice > (cityCinemas + j)->priceList.avgPrice) {
                cinema temp = *(cityCinemas + i);
                *(cityCinemas + i) = *(cityCinemas + j);
                *(cityCinemas + j) = temp;
            }
        }
    }
}

void sortDenumire(int n, cinema *cityCinemas) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if(strcmp((cityCinemas + i)->denumirea, (cityCinemas + j)->denumirea) > 0) {
                cinema temp = *(cityCinemas + i);
                *(cityCinemas + i) = *(cityCinemas + j);
                *(cityCinemas + j) = temp;
            }
        }
    }
}

void removeStruct(int *n, cinema *cityCinemas) {
    int option;
    cinema *temp;
    temp = (cinema *)calloc(*n - 1, sizeof(cinema));
    printf("\nInput number of structure(0..)");
    scanf("%d", &option);

    for (int i = 0, k = 0; i < *n; i++, k++) {
        if(i != option) {
            *(temp + k) = *(cityCinemas + i);
        }
        else {
            k--;
        }
    }
    *n = *n - 1;
    for (int i = 0; i < *n; i++) {
        *(cityCinemas + i) = *(temp + i);
    }
}