#include <stdio.h>
#include <stdlib.h>

void quickSort(int *vect, int low, int high);
int partition(int *vect, int low, int high);
void swap(int *a, int *b);

void main() {
    int *vect, n;
    scanf("%d", &n);

    vect = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", vect + i);
        for (int j = 0; j < i; j++) {
            if(*(vect + i) == *(vect + j)) {
                n--;
                i--;
            }
        }
    }

    quickSort(vect, 0, n - 1);
    for (int i = 0; i < n; i++){
        printf("%d ", *(vect + i));
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition (int arr[], int low, int high){
    int pivot = arr[high]; 
    int i = (low - 1); 
 
    for (int j = low; j <= high - 1; j++){
        if (arr[j] < pivot){
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
void quickSort(int arr[], int low, int high){
    if (low < high){

        int pi = partition(arr, low, high);
 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}