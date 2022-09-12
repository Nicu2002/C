#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sdtbool.h>

typedef struct {
    char nume[15];
    char prenume[15];
    struct {
        int mate;
        int rom;
        int eng;
    } nota;
} elev;

//citire din fish, afis. in alt fish, afisare in consola, adaugam alta structura
void citire(int n, elev *grupa, FILE *pf) {
    int i;
    while (!feof(pf)) {
        fscanf(pf, "%s\n %s\n %d\n %d\n %d\n", (grupa+i)->nume, (grupa+i)->prenume, &(grupa+i)->nota.mate, &(grupa+i)->nota.rom, &(grupa+i)->nota.eng);
        i++;
    }
}

void consola(int n, elev *grupa) {
    for (int i=0; i<n; i++) {
        printf("%s", (grupa+i)->nume);
    }
}

void readNewObject(int n, elev *grupa){
    printf("nume : ");
    scanf("%s", (grupa + n - 1)->nume);
    printf("prenume : ");
    scanf("%s", (grupa + n - 1)->prenume);
    printf("mate : ");
    scanf("%d", &(grupa + n - 1)->nota.mate);
    printf("rom : ");
    scanf("%d", &(grupa + n - 1)->nota.rom);
    printf("eng : ");
    scanf("%d", &(grupa + n - 1)->nota.eng);
}

void bubbleSort(int n, elev *grupa) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if(strcmp((grupa + j)->nume, (grupa + j + 1)->nume) > 0) {
                elev temp = *(grupa + j);
                *(grupa + j) = *(grupa + j + 1);
                *(grupa + j + 1) = temp;
            }
        }
    }
}

void outputFile(int n, elev *grupa, FILE *pf) {
    pf = fopen("output.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(pf, )
    }
}

void main() {
    int n;
    printf("input nr studenti:");
    scanf("%d", &n);
    elev *grupa;
    grupa=(elev*)malloc(n*sizeof(elev));
    FILE *pf;
    pf=fopen("input.txt", "r");
    if (!pf)
        return 1;
    citire(n, grupa, pf);
    fclose(pf);
    n++;
    grupa = (elev *)realloc(grupa, n * sizeof(elev));

    readNewObject(n, grupa);

    bubleSort()
}
