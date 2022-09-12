#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void initData(char *arr, int *n);
void inversateArr(char *arr, int n);
void showConsole(char *arr, int n);

void main() {
    char *arr;
    int n;
    printf("input numeber of chars : ");
    scanf("%d", &n);
    arr = malloc(n * sizeof(char));

    initData(arr, &n);
    inversateArr(arr, n);
    showConsole(arr, n);
}

void initData(char *arr, int *n) {
    printf("input string : ");
    scanf("%s", arr);
    if(*n != strlen(arr)) {
        *n = strlen(arr);
        arr = realloc(arr, *n * sizeof(char));
    }
    FILE *pf;
    pf = fopen("lucru.txt", "w");
    fprintf(pf, "%s", arr);
    fclose(pf);
}

void inversateArr(char *arr, int n) {
    for (int i = 0; i < n / 2; i++) {
        char temp = arr[i];  
        arr[i] = arr[n - i - 1];  
        arr[n - i - 1] = temp;  
    }
    FILE *pf;
    pf = fopen("lucru.txt", "w");
    fprintf(pf, "%s", arr);
    fclose(pf);
}

void showConsole(char *arr, int n) {
    printf("\nlungimea : %d", n);
    printf("\nstring : %s", arr);
}