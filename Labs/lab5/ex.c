#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Pricelist {
    int lowlvl;
    int avglvl;
    int toplvl;
};

struct Cinematograf {
    char name[10];
    char address[20];
    char phone[10];
    int space;
    struct Pricelist price;
};

void inputInfo(struct Cinematograf *cinemas, int n);
void viewData(struct Cinematograf *cinemas, int n);
void menu(struct Cinematograf *cinemas, int n);
void sortMenu(struct Cinematograf *cinemas, int n, bool direction);
void sortType(struct Cinematograf *cinemas, int n, bool direction);
void swap(int *a, int *b);
void advancedSwap(struct Cinematograf *cinemas, int a, int b);

void heapSort(struct Cinematograf *cinemas, int n, bool direction);
void heapify(struct Cinematograf *cinemas, int n, int root, bool direction);

void quickSort(struct Cinematograf *cinemas, int low, int high, bool direction);
int partion(struct Cinematograf *cinemas, int low, int high, bool direction);

void main() {
    struct Cinematograf cinemas[5];
    int n;
    printf("input number of cinemas : ");
    scanf("%d", &n);
    menu(cinemas, n);
}

void menu(struct Cinematograf *cinemas, int n) {
    printf("\n******** menu ********\n");
    printf("1.Citirea datelor.");
    printf("\n2.Afisarea datelor.");
    printf("\n3.Sortarea crescator a datelor.");
    printf("\n4.Sortarea descrescator a datelor.");
    printf("\n0.Exit.");
    int option;
    printf("\n->optiunea : ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            inputInfo(cinemas, n);
            break;
        case 2:
            viewData(cinemas, n);
            break;
        case 3:
            sortMenu(cinemas, n, true);
            break;
        case 4:
            sortMenu(cinemas, n, false);
            break;
        case 0:
            exit(1);
    }
}

void inputInfo(struct Cinematograf *cinemas, int n) {
    for (int i = 0; i < n; i++) {
        printf("*** Datele pentru cinematograful nr. %d : \n", i + 1);
        printf("--> Denumirea cinematografului : ");
        scanf("%s", &(cinemas + i)->name);
        printf("\n--> Adresa cinematografului : ");
        scanf("%s", (cinemas + i)->address);
        printf("\n--> Numarul de telefon : ");
        scanf("%s", (cinemas + i)->phone);
        printf("\n--> Numarul de locuri : ");
        scanf("%d", &(cinemas + i)->space);
        printf("\n--> Pretul locurilor ieftine : ");
        scanf("%d", &(cinemas + i)->price.lowlvl);
        printf("\n--> Pretul locurilor medii : ");
        scanf("%d", &(cinemas + i)->price.avglvl);
        printf("\n--> Pretul locurilor scumpe : ");
        scanf("%d", &(cinemas + i)->price.toplvl);
    }
    menu(cinemas, n);
}

void viewData(struct Cinematograf *cinemas, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n-->' %s '<--", (cinemas + i)->name);
        printf("\nAddress : %s", (cinemas + i)->address);
        printf("\nPhone : %s", (cinemas + i)->phone);
        printf("\nLocuri : %d", (cinemas + i)->space);
        printf("\nLow price : %d", (cinemas + i)->price.lowlvl);
        printf("\nAverage price : %d", (cinemas + i)->price.avglvl);
        printf("\nTop price : %d", (cinemas + i)->price.toplvl);
    }
    menu(cinemas, n);
}

// void sortType(struct Cinematograf *cinemas, int n, bool direction) {
//     printf("***** Sort type menu *****\n");
//     printf("1. Dupa denumire.");
//     printf("\n2. Dupa adresa.");
//     printf("\n3. Dupa telefon.");
//     printf("\n4. Dupa locuri.");
//     printf("\n5. Dupa pretul minim.");
//     printf("\n6. Dupa pretul average.");
//     printf("\n7. Dupa pretul maxim.");
//     printf("\n0. Main menu.");
//     int option;
//     char atr[15];
//     printf("\n--> Optiunea : ");
//     scanf("%d", &option);

//     switch(option) {
//         case 1:
//             strcpy(atr, "name");
//             sortMenu(cinemas, n, direction, atr);
//             break;
//         case 2:
//             sortMenu(cinemas, n, direction, 1);
//             break;
//         case 3:
//             sortMenu(cinemas, n, direction, 1);
//             break;
//         case 4:
//             sortMenu(cinemas, n, direction, 0);
//             break;
//         case 5:
//             sortMenu(cinemas, n, direction, 0);
//             break;
//         case 6:
//             sortMenu(cinemas, n, direction, 0);
//             break;
//         case 7:
//             sortMenu(cinemas, n, direction, 0);
//             break;
//         case 0:
//             exit(1);
//     }
// }

void sortMenu(struct Cinematograf *cinemas, int n, bool direction) {
    printf("***** Sort menu *****\n");
    printf("1. Quick sort.");
    printf("\n2. Heap sort.");
    printf("\n0. Main menu");
    int option;
    printf("\n--> Optiunea : ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            quickSort(cinemas, 0, n - 1, direction);
            menu(cinemas, n);
            break;
        case 2:
            heapSort(cinemas, n, direction);
            break;
        case 0:
            menu(cinemas, n);
    }
}

void heapSort(struct Cinematograf *cinemas, int n, bool direction) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(cinemas, n, i, direction);
    }
    for (int i = n - 1; i > 0; i--) {
        advancedSwap(cinemas, 0, i);

        heapify(cinemas, i, 0, direction);
    }
    menu(cinemas, n);
}

void heapify(struct Cinematograf *cinemas, int n, int root, bool direction) {
    int largest = root,
        left = 2 * root + 1,
        right = 2 * root + 2;
    
    if(direction == true) {
        if(left < n && (cinemas + largest)->space < (cinemas + left)->space) {
            largest = left;
        }
        if(right < n && (cinemas + largest)->space < (cinemas + right)->space) {
            largest = right;
        }
    }
    else {
        if(left < n && (cinemas + largest)->space > (cinemas + left)->space) {
            largest = left;
        }
        if(right < n && (cinemas + largest)->space > (cinemas + right)->space) {
            largest = right;
        }
    }

    if(largest != root) {
        advancedSwap(cinemas, root, largest);

        heapify(cinemas, n, largest, direction);
    }
}

void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

void advancedSwap(struct Cinematograf *cinemas, int a, int b) {
    swap(&(cinemas + a)->space, &(cinemas + b)->space);
    swap(&(cinemas + a)->price.lowlvl, &(cinemas + b)->price.lowlvl);
    swap(&(cinemas + a)->price.avglvl, &(cinemas + b)->price.avglvl);
    swap(&(cinemas + a)->price.toplvl, &(cinemas + b)->price.toplvl);

    char aux[20];

    strcpy(aux, (cinemas + a)->name);
    strcpy((cinemas + a)->name, (cinemas + b)->name);
    strcpy((cinemas + b)->name, aux);

    strcpy(aux, (cinemas + a)->address);
    strcpy((cinemas + a)->address, (cinemas + b)->address);
    strcpy((cinemas + b)->address, aux);

    strcpy(aux, (cinemas + a)->phone);
    strcpy((cinemas + a)->phone, (cinemas + b)->phone);
    strcpy((cinemas + b)->phone, aux);
}

void quickSort(struct Cinematograf *cinemas, int low, int high, bool direction) {
    if(low < high) {
        int pi = partion(cinemas, low, high, direction);

        quickSort(cinemas, low, pi - 1, direction);
        quickSort(cinemas, pi + 1, high, direction);
    }
}

int partion(struct Cinematograf *cinemas, int low, int high, bool direction) {
    int pivot = (cinemas + high)->space;
    int i = low - 1;
    if(direction == true) {
        for (int j = low; j < high; j++) {
            if((cinemas + j)->space < pivot) {
                i++;
                advancedSwap(cinemas, j, i);
            }
        }  
    }
    else {
        for (int j = low; j < high; j++) {
            if((cinemas + j)->space > pivot) {
                i++;
                advancedSwap(cinemas, j, i);
            }
        } 
    }
    advancedSwap(cinemas, i + 1, high);

    return (i + 1);
}

