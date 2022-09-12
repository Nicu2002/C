#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Period {
    int startYear;
    int finishYear;
};

typedef struct Carte{
    char author[20];
    char title[20];
    struct Period years;
    int pages;
} book;

void readData(int N, book *library);
void clearBuffer();
void showData(book *library, int N);
void bubbleSort(int N, book *library);
void swap(book *a, book *b);

void main() {
    int N;
    book *library;

    printf("inpun Number of books : ");
    scanf("%d", &N);
    library = (book *)calloc(N, sizeof(book));

    readData(N, library);
    showData(library, N);

    bubbleSort(N, library);
    printf("\nDupa sortare");
    showData(library, N);
}

void readData(int N, book *library){
    printf("\n--- Introducerea datelor ---\n");
    for (int i = 0; i < N; i++) {
        printf("<---- Book number %d ---->\n", i + 1);

        clearBuffer();
        printf("\nauthor : ");  scanf("%[^\n]%*c", (library + i)->author);
        printf("\ntitle : ");  scanf("%[^\n]%*c", (library + i)->title);
        printf("\nfirst year : ");  scanf("%d", &(library + i)->years.startYear);
        printf("\nlast year : ");  scanf("%d", &(library + i)->years.finishYear);
        if((library + i)->years.finishYear < (library + i)->years.startYear){
            printf("Input year is incorect...");
            exit(1);
        }
        printf("\npages : ");  scanf("%d", &(library + i)->pages);


    }
}

void clearBuffer() {
    char c;
    do{
        c = getchar();
    } while (c != '\n');
}

void showData(book *library, int N) {
    printf("\n---Show data---\n");
    for (int i = 0; i < N; i++) {
        printf("%s | %s | %d | %d | %d\n", (library + i)->author, (library + i)->title, (library + i)->years.startYear, (library + i)->years.finishYear, (library + i)->pages);
    }
}

void bubbleSort(int N, book *library) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if((library + j)->pages > (library + j + 1)->pages) {
                swap(library + j, library + j + 1);
            }
        }
    }
}

void swap(book *a, book *b) {
    book temp = *a;
    *a = *b;
    *b = temp;
}
