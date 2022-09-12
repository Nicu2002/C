#include "liste.h"
#include <stdio.h>

int main() {
    int n;
    printf("input number of elements : ");
    scanf("%d", &n);

    initList(n);
    initData();
    showData();
    searchBySurface();
    modifyByPosition();
    showData();
    findLastPosition();
    swap(1, 3);
    showData();
    sortList(n);
    showData();

    return 0;
}