#include <stdio.h>
#include <string.h>
#include "canalTv.h"

void readData(canal tv[10], int n);
void showData(canal tv[10], int n);
void clearBuffer();

void RadixSort(canal tv[10], int n);
void counting_sort_for_radix(int n, canal tv[10], int exp);
int max_num(int n, canal tv[10]);

void insertSort(int n, canal tv[10]);

void main() {
    canal tv[10];
    int n;
    printf("Input chanals number : ");
    scanf("%d", &n);

    readData(tv, n);
    showData(tv, n);

    RadixSort(tv, n);
    printf("\nSortarea canalelor crescator dupa rating : \n");
    showData(tv, n);

    insertSort(n, tv);
    printf("\nSortarea canalelor descrescator dupa denumire : \n");
    showData(tv, n);
}

void readData(canal tv[10], int n) {
    for (int i = 0; i < n; i++) {
        printf("\n---Read data for chanel #%d ---", i + 1);
        clearBuffer();
        printf("\nname : ");  scanf("%[^\n]%*c", tv[i].name);
        printf("\ncountry : ");  scanf("%[^\n]%*c", tv[i].country);
        printf("\nphone : ");  scanf("%[^\n]%*c", tv[i].phone);
        printf("\ntype : ");  scanf("%[^\n]%*c", tv[i].type);
        printf("\nrating : ");  scanf("%d", &tv[i].rating);
    }
}

void showData(canal tv[10], int n) {
    printf("\n---Show data---\n");
    for (int i = 0; i < n; i++) {
        printf("%s | %s | %s | %s | %d\n", tv[i].name, tv[i].country, tv[i].phone, tv[i].type, tv[i].rating);
    }
}

void clearBuffer() {
    char c;
    do{
        c = getchar();
    } while (c != '\n');
}

void RadixSort(canal tv[10], int n) {
    int m = max_num(n, tv);

    for (int exp = 1; m / exp > 0; exp *= 10) {
        counting_sort_for_radix(n, tv, exp);
    }
}

void counting_sort_for_radix(int n, canal tv[10], int exp) {
    canal sorted_tv[10];

    int count_arr[10] = {0};
        
    for (int i = 0; i < n; i++){
        ++count_arr[(tv[i].rating / exp) % 10];
    }
    for (int i = 1; i < 10; i++) {
        count_arr[i] += count_arr[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        sorted_tv[count_arr[(tv[i].rating / exp) % 10] - 1] = tv[i];
        --count_arr[(tv[i].rating / exp) % 10];
    }
    for (int i = 0; i < n; i++) {
        tv[i] = sorted_tv[i];
    }
}

int max_num(int n, canal tv[10]) {
    int max = tv[0].rating;
    for (int i = 1; i < n; i++) {
        if(max < tv[i].rating) {
            max = tv[i].rating;
        }
    }
    return max;
}

void insertSort(int n, canal tv[10]) {
    int j;
    canal key;
    for (int i = 1; i < n; i++){
        key = tv[i];
        j = i - 1;
        while (j >= 0 && strcmp(tv[j].name, key.name) < 0) {
            tv[j + 1] = tv[j];
            j--;
        }
        tv[j + 1] = key;
    }
}