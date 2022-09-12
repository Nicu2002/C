#include "cozi.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Queue *coada;

void initList(int n) {
    coada = (Queue *)malloc(sizeof(Queue));
    Stat *el;
    for(int i = 0; i < n; i++){
		el=(Stat*) malloc (sizeof(Stat));
		
		if(el == NULL){
			return;
		}
		if(i == 0){
			coada->head = el;
            coada->tail = el;
        }
		else{
            coada->tail->next = el;
			coada->tail = el;
		}
        coada->tail->next = NULL;
	}
}

void initData() {
    Stat *el = coada->head;

    while(el != NULL) {
        printf("Name : ");
		scanf("%s",el->data.name);
		printf("Capital : ");
		scanf("%s",el->data.capital);
        printf("Surface(km2) : ");
		scanf("%d",&el->data.surface);
        printf("Population : ");
		scanf("%d",&el->data.population);
        printf("PIT : ");
		scanf("%d",&el->data.PIT);
        el = el->next;
    }
}

void showData() {
    Stat *el = coada->head;

    while(el != NULL) {
        printf("\nName : %s", el->data.name);
		printf("\nCapital : %s", el->data.capital);
        printf("\nSurface(km2) : %d", el->data.surface);
        printf("\nPopulation : %d", el->data.population);
        printf("\nPIT : %d", el->data.PIT);
        el = el->next;
    }
}

void searchBySurface() {
    Stat *el = coada->head;
    int counter = 0;
    while(el != NULL) {
        if(el->data.surface > 10000) {
            printf("\n*Country %s is big(%d)", el->data.name, el->data.surface);
            counter++;
        }
        el = el->next;
    }
    if(counter == 0) {
        printf("\nWorld is small!");
    }
}

void modifyByPosition(int n) {
    int k, i = 1;
    printf("input k (counting starts with 1):");
    scanf("%d", &k);

    Stat *el = coada->head;
    while(el != NULL) {
        if(i == k) {
            printf("Name : ");
            fflush(stdin);
            scanf("%s",el->data.name);
		    printf("Capital : ");
		    scanf("%s",el->data.capital);
            printf("Surface(km2) : ");
		    scanf("%d",&el->data.surface);
            printf("Population : ");
		    scanf("%d",&el->data.population);
            printf("PIT : ");
		    scanf("%d",&el->data.PIT);
        }
        el = el->next;
        i++;
    } 
}

void findLastPosition() {
    Stat *pt = coada->tail;

    printf("\nAdresse of last element : %p", pt);
}

void swap(Stat *a, Stat *b) {
    Stat *na, *nb;
    Stat t;
    na = a->next;
    nb = b->next;

    t = *a;
    *a = *b;
    *b = t;

    a->next = na;
    b->next = nb;
}

void sortList(int n) {
    Stat *el = coada->head;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) {
            if(el->data.population > el->next->data.population) {
                swap(el, el->next);
            }
            el = el->next;
        }
        el = coada->head;
    }
        
}