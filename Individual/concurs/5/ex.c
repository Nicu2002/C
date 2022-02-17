#include <stdio.h>
#include <stdlib.h>

void selection_sort(int n, int *arr);
void swap(int *a, int *b);

int main() {
    int *arr = NULL;
    int n;

    scanf("%d", &n);

    arr = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }

    selection_sort(n, arr);
    for (int i = 0; i < n; i++) {
        printf("%d ", *(arr + i));
    }
    return 1;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int n, int *arr) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if(*(arr + i) > *(arr + j)) {
                swap(arr + i, arr + j);
            }
        }
    }
}