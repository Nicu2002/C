#include <stdio.h> 
#include <stdbool.h>
#include <string.h> 

 

//sorta dupa prima disciplina 

struct Disciplina { 

    char numeDs[15]; 

    int notaDs;    

}; 

struct BAC{ 

    char nume[10]; 

    char prenume[10]; 

    struct Disciplina d[4]; 

}; 

void citire(struct BAC *elev_ref, int nr); 

void afisare(struct BAC *elev_ref, int nr); 

float media_elev(struct BAC *elev_ref, int i);

void bubble_sort(struct BAC *elev_ref, int nr);

void selectionSort(struct BAC *elev_ref, int nr);

int main() 

{ 

   struct BAC elev[5]; 

   int n; 

   printf("intruduceti nr elevilor\n"); 

   printf("n ="); scanf("%d", &n); 

   citire(elev, n); 

   afisare(elev, n); 

    

   float media[n]; 

   for (int i = 0; i < n; i++){ 

       media[i] = media_elev(elev, i); 

   } 
    
    for (int i = 0; i < n; i++){ 
       printf("\n%s %s:  %.2f", (elev+i)->nume, (elev+i)->prenume, media[i]); 
    }
    bubble_sort(elev, n);
    selectionSort(elev, n);
    return 0; 
} 

 

void citire(struct BAC *elev_ref, int nr){ 

     

    for (int i = 0; i < nr; i++){ 

        printf("\nIntroduceti datele elevului %i", i+1); 

        printf("\nNume:\n"); 

        scanf("%s", (elev_ref+i)->nume); 

        printf("Prenume:\n"); 

        scanf("%s", (elev_ref+i)->prenume); 

        for(int j = 0; j < 3; j++){ 

            printf("Introduceti disciplina %i\n", j+1); 

            scanf("%s", (elev_ref+i)->d[j].numeDs); 

            printf("Nota:\n"); 

            scanf("%i", &(elev_ref+i)->d[j].notaDs); 

        } 

    } 

} 

 

void afisare(struct BAC *elev_ref, int nr){ 

    printf("-------Date despre elevi din array--------\n"); 

    for (int i = 0; i < nr; i++){ 

        printf("\n%s %s ->", (elev_ref+i)->nume, (elev_ref+i)->prenume); 

        for(int j = 0; j < 3; j++){ 

            printf(" %s =", (elev_ref+i)->d[j].numeDs); 

            printf(" %i;", (elev_ref+i)->d[j].notaDs); 

        } 

    }     

} 

 

float media_elev(struct BAC *elev_ref, int i){ 

    float sum = 0;  

    for(int j = 0; j < 3; j++){ 

        sum += (elev_ref+i)->d[j].notaDs; 

    } 

return sum/3; 

} 

void bubble_sort(struct BAC *elev_ref, int nr){
    bool sorted;
    int i = 0;
    do {
        int p = i;
        sorted = true;
        for (int j = 0; j < nr - 1; j++) {
            if((elev_ref + j)->d[0].notaDs > (elev_ref + j + 1)->d[0].notaDs) {
                p = j;
            }
        }
        char aux[10];

        strcpy(aux, (elev_ref + i)->nume);
        strcpy((elev_ref + i)->nume, (elev_ref + p)->nume);
        strcpy((elev_ref + p)->nume, aux);

        strcpy(aux, (elev_ref + i)->prenume);
        strcpy((elev_ref + i)->prenume, (elev_ref + p)->prenume);
        strcpy((elev_ref + p)->prenume, aux);

        for (int j = 0; j < 3; j++) {
            strcpy(aux, (elev_ref + i)->d[j].numeDs);
            strcpy((elev_ref + i)->d[j].numeDs, (elev_ref + p)->d[p].numeDs);
            strcpy((elev_ref + p)->d[p].numeDs, aux);

            int temp = (elev_ref + i)->d[j].notaDs;
            (elev_ref + i)->d[j].notaDs = (elev_ref + p)->d[j].notaDs;
            (elev_ref + p)->d[j].notaDs = temp;
        }

        i++;
    } while (!sorted);
    printf("\nDupa sortarea bubble : \n");
    afisare(elev_ref, nr);
}

void selectionSort(struct BAC *elev_ref, int nr) {
    for (int i = 0; i < nr - 1; i++) {
        int p = i;
        for (int j = i + 1; j < nr; j++) {
            if((elev_ref + j)->d[0].notaDs > (elev_ref + p)->d[0].notaDs) {
                p = j;
            }
        }
        char aux[10];

        strcpy(aux, (elev_ref + i)->nume);
        strcpy((elev_ref + i)->nume, (elev_ref + p)->nume);
        strcpy((elev_ref + p)->nume, aux);

        strcpy(aux, (elev_ref + i)->prenume);
        strcpy((elev_ref + i)->prenume, (elev_ref + p)->prenume);
        strcpy((elev_ref + p)->prenume, aux);

        for (int j = 0; j < 3; j++) {
            strcpy(aux, (elev_ref + i)->d[j].numeDs);
            strcpy((elev_ref + i)->d[j].numeDs, (elev_ref + p)->d[p].numeDs);
            strcpy((elev_ref + p)->d[p].numeDs, aux);

            int temp = (elev_ref + i)->d[j].notaDs;
            (elev_ref + i)->d[j].notaDs = (elev_ref + p)->d[j].notaDs;
            (elev_ref + p)->d[j].notaDs = temp;
        }
    }
    printf("\nDupa sortare prin selectie : \n");
    afisare(elev_ref, nr);
}