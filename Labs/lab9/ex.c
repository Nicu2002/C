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
void competitie();
void unifyFiles();

void main() {
    int n;
    printf("input n :");
    scanf("%d", &n);
    cinema *cityCinemas;
    cityCinemas = (cinema *)calloc(n, sizeof(cinema));
    competitie();
    completeFile(cityCinemas, n);
    unifyFiles();
}

//completarea fisierului cu ajutorul programului 
void completeFile(cinema *cityCinemas, int n) {
    FILE *pf;
    pf = fopen("lucru.txt", "w");
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

void competitie() {
    int *A, N, maxRes, loseNum = 0;
    FILE *pf;
    pf = fopen("DIST.txt", "r");

    fscanf(pf, "%d", &N);
    printf("\n----------------------Problema de bac------------------");
    printf("\nNumarul de participanti : %d", N);
    A = malloc(N * sizeof(int));
    printf("\nRezultatele participantilor: ");
    for (int i = 0; i < N; i++) {
        fscanf(pf, "%d ", A + i);
        printf("%d ", *(A + i));
        if(*(A + i) == 0) {
            loseNum += 1;
        }
    }
    fclose(pf);

    maxRes = *A;
    for (int i = 1; i < N; i++) {
        if(maxRes < *(A + i)) {
            maxRes = *(A + i);
        }
    }
    printf("\n /Distanta maxima : %d", maxRes);
    printf("\n /Numarul de esuari : %d", loseNum);
    printf("\n-------------------------------------------------------");

    FILE *pOut;
    pOut = fopen("output.txt", "w");
    fprintf(pOut, "%d\n", maxRes);
    fprintf(pOut, "%d", loseNum);
    fclose(pOut);
}

void unifyFiles() {
    FILE *pfa, *pfb, *pfc;
    pfa = fopen("lucru.txt", "r");
    pfb = fopen("output.txt", "r");
    pfc = fopen("RESULT.txt", "w");
    int c;
    while((c = fgetc(pfa))!=EOF) {
        fputc(c, pfc);
    }
    while((c = fgetc(pfb))!=EOF) {
        fputc(c, pfc);
    }
    fclose(pfa);
    fclose(pfb);
    fclose(pfc);
}