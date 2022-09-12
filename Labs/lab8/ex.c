#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void fillFile(int *n, char *vect);
void replaceSpaces(int *n, char *vect);
void renameFile(int *n);
void appendNewData(int numOfChars);
void calcAvg(int numOfChars, int n);

void main() {
    int n;
    char *vect;

    printf("input max number of chars : ");
    scanf("%d", &n);
    fillFile(&n, vect);
}

void fillFile(int *n, char *vect) {
    vect = malloc(*n * sizeof(char));
    printf("string : ");
    fflush(stdin);
    scanf("%[^\n]%*c", vect);

    FILE *pf;
    pf = fopen("lucru.txt", "w");
    fputs(vect, pf);
    fclose(pf);

    if(*n != strlen(vect)) {
        *n = strlen(vect);
        vect = realloc(vect, *n * sizeof(char));
    }
    replaceSpaces(n, vect);
}

void replaceSpaces(int *n, char *vect) {
    FILE *pf;
    pf = fopen("lucru.txt", "r");
    char ch;
    int i = 0;
    printf("New string : ");
    while((ch = fgetc(pf)) != EOF) {
        if(ch == ' ') {
            *(vect + i) = '*';
        }
        printf("%c", *(vect + i));
        i++;
    }

    fclose(pf);

    pf = fopen("lucru.txt", "w");
    fputs(vect, pf);
    fclose(pf);

    renameFile(n);
}

void renameFile(int *n) {
    rename("lucru.txt", "binarFile.bin");
    appendNewData(*n);
}

void appendNewData(int numOfChars) {
    int *vect, n;
    printf("\ninput number of random numbers :");
    scanf("%d", &n);

    vect = malloc(n * sizeof(int));
    srand(time(0));
    FILE *pf;
    pf = fopen("binarFile.bin", "a");
    for (int i = 0; i < n; i++) {
        *(vect + i) = rand() % 100 - 50;
        fwrite(vect + i, sizeof(int), 1, pf);
    }
    for (int i = 0; i < n; i++) {
        printf(" %d", *(vect + i));
    }
    free(vect);
    fclose(pf);

    calcAvg(numOfChars, n);
}

void calcAvg(int numOfChars, int n) {
    int *temp;
    double avg;
    temp = calloc(n, sizeof(int));
    FILE *pf;
    pf = fopen("binarFile.bin", "rb");

    fseek(pf, numOfChars, SEEK_SET);
    fread(temp, sizeof(int), n, pf);

    for (int i = 0; i < n; i++) {
        avg += *(temp + i);
    }
    avg /= n;
    fclose(pf);

    FILE *resFile;
    resFile = fopen("output.txt", "w");
    fprintf(resFile, "%.3lf", avg);
    fclose(resFile);

    remove("binarFile.bin");
}
