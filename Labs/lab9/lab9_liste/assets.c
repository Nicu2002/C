#include "liste.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Stat *head;

void initList(int n) {
	Stat *el,*nod;  
	for(int i = 0; i < n; i++){
		el=(Stat*) malloc (sizeof(Stat));
		
		if(el == NULL){
			return;
		}
		if(i == 0){
			head = el;
			nod = el;
    	}
		else{
			nod->next = el;
			nod = el;
		}
	}
	nod->next = NULL;
}

void initData() {
    Stat *el = head;

    while(el != NULL) {
        printf("Name : ");
		scanf("%s",el->name);
		printf("Capital : ");
		scanf("%s",el->capital);
        printf("Surface(km2) : ");
		scanf("%d",&el->surface);
        printf("Population : ");
		scanf("%d",&el->population);
        printf("PIT : ");
		scanf("%d",&el->PIT);
        el = el->next;
    }
}

void showData() {
    Stat *el = head;

    while(el != NULL) {
        printf("\nName : %s", el->name);
		printf("\nCapital : %s", el->capital);
        printf("\nSurface(km2) : %d", el->surface);
        printf("\nPopulation : %d", el->population);
        printf("\nPIT : %d", el->PIT);
        el = el->next;
    }
}

void searchBySurface() {
    Stat *el = head;
    int counter = 0;
    while(el != NULL) {
        if(el->surface > 10000) {
            printf("\n*Country %s is big(%d)", el->name, el->surface);
            counter++;
        }
        el = el->next;
    }
    if(counter == 0) {
        printf("\nWorld is small!");
    }
}

void modifyByPosition() {
    int k, i = 1;
    printf("input k (counting starts with 1):");
    scanf("%d", &k);

    Stat *el = head;
    while(el != NULL) {
        if(i == k) {
            printf("Name : ");
            fflush(stdin);
            scanf("%s",el->name);
		    printf("Capital : ");
		    scanf("%s",el->capital);
            printf("Surface(km2) : ");
		    scanf("%d",&el->surface);
            printf("Population : ");
		    scanf("%d",&el->population);
            printf("PIT : ");
		    scanf("%d",&el->PIT);
        }
        el = el->next;
        i++;
    } 
}

void findLastPosition() {
    Stat *el = head;
    Stat *pt;

    while(el->next != NULL) {
        pt = el->next;
        el = el->next;
    }

    printf("\nAdresse of last element : %p", pt);
}

void swap(int a, int b) {
    if(a == b) {
        return;
    }
    int k = 1;
    Stat *prevNod1 = NULL, *prevNod2 = NULL, *node1 = head, *node2 = head, *temp;
    while(k != a && node1 != NULL) {
        prevNod1 = node1;
        node1 = prevNod1->next;
        k++;
    }
    k = 1;
    while(k != b && node2 != NULL) {
        prevNod2 = node2;
        node2 = prevNod2->next;
        k++;
    }

    if(node1 != NULL && node2 != NULL) {  
          
        if(prevNod1 != NULL)  
            prevNod1->next = node2;          
        else  
            head  = node2;  
          
        if(prevNod2 != NULL)  
            prevNod2->next = node1;  
        else  
            head  = node1;  
          
        temp = node1->next;   
        node1->next = node2->next;   
        node2->next = temp;       
    }      
    else{  
        printf("Error!\n");  
    }  
}

void sortList(int n) {
    Stat *el = head, *nod = head;
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if(el->population > el->next->population) {
                swap(i, j);
            }
            el = el->next;
        }
        nod = nod->next;
        el = nod;
    }
}
