#include "cozi.h"
#include <stdio.h>

int main() {
    int n;
    printf("input number of elements : ");
    scanf("%d", &n);

    initList(n);
    initData();
    showData();
    searchBySurface();
    modifyByPosition(n);
    showData();
    findLastPosition();
    sortList(n);
    showData();

    return 0;
}