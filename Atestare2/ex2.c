#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Date {
    int zi;
    int luna;
    int an;
} Date;

typedef struct Departament {
    char nume_dep[20];
    char adresa_dep[20];
    int nr_angajati;
    Date data_creare;
} Departament;
char file[20];
void initDeps(Departament *departamente, int n);
void initDataInFile(Departament *departamente, int n);
void readFile(int n);

void main() {
    int n;
    Departament *departamente;
    printf("input number of departaments :");
    scanf("%d", &n);

    departamente = malloc(n * sizeof(Departament));

    initDeps(departamente, n);
    initDataInFile(departamente, n);
    readFile(n);
}

void initDeps(Departament *departamente, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n---------------------\n");
        printf("numele departamentului %d: ", i + 1);
        scanf("%s", (departamente + i)->nume_dep);
        printf("adresa departamentului %d: ", i + 1);
        scanf("%s", (departamente + i)->adresa_dep);
        printf("nr de angajati din departamentul %d: ", i + 1);
        scanf("%d", &(departamente + i)->nr_angajati);
        printf("data (luna ziua anul)");
        scanf("%d %d %d", &(departamente + i)->data_creare.luna, &(departamente + i)->data_creare.zi, &(departamente + i)->data_creare.an);
    }
}

void initDataInFile(Departament *departamente, int n) {
    printf("name of file : ");
    fflush(stdin);
    scanf("%s", file);
    FILE *pf;
    pf = fopen(file, "w");
    for (int i = 0; i < n; i++) {
        fprintf(pf, "%s ", (departamente + i)->nume_dep);
        fprintf(pf, "%s ", (departamente + i)->adresa_dep);
        fprintf(pf, "%d ", (departamente + i)->nr_angajati);
        fprintf(pf, "%d %d %d\n", (departamente + i)->data_creare.luna, (departamente + i)->data_creare.zi, (departamente + i)->data_creare.an);
    }
    fclose(pf);
}

void readFile(int n) {
    Departament *anotherDepartamente;
    anotherDepartamente = malloc(n * sizeof(Departament));
    FILE *pf;
    pf = fopen(file, "r");
    for (int i = 0; i < n; i++) {
        fscanf(pf, "%s ", (anotherDepartamente + i)->nume_dep);
        fscanf(pf, "%s", (anotherDepartamente + i)->adresa_dep);
        fscanf(pf, "%d", &(anotherDepartamente + i)->nr_angajati);
        fscanf(pf, "%d %d %d\n", &(anotherDepartamente + i)->data_creare.luna, &(anotherDepartamente + i)->data_creare.zi, &(anotherDepartamente + i)->data_creare.an);
    }

    fclose(pf);

    for (int i = 0; i < n; i++) {
        printf("%s", (anotherDepartamente + i)->nume_dep);
        printf("|%s", (anotherDepartamente + i)->adresa_dep);
        printf("|%d", (anotherDepartamente + i)->nr_angajati);
        printf("|%d %d %d\n", (anotherDepartamente + i)->data_creare.luna, anotherDepartamente->data_creare.zi, anotherDepartamente->data_creare.an);
    }
}